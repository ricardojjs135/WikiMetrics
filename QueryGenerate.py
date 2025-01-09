import sys
import json
import time
from SPARQLWrapper import SPARQLWrapper, JSON
from collections import defaultdict
import os
from datetime import datetime, timedelta

endpoint_url = "https://query.wikidata.org/sparql"

base_query = """SELECT DISTINCT ?human ?humanLabel ?sex_or_genderLabel ?country_of_citizenshipLabel 
  ?date_of_birth ?date_of_death ?professionLabel ?religionLabel ?educationLabel WHERE {{
  ?human wdt:P31 wd:Q5.
  ?human wdt:P27 wd:Q155.
  OPTIONAL {{ ?human wdt:P21 ?sex_or_gender. }}
  OPTIONAL {{ ?human wdt:P569 ?date_of_birth. }}
  OPTIONAL {{ ?human wdt:P570 ?date_of_death. }}
  OPTIONAL {{ ?human wdt:P106 ?profession. }}
  OPTIONAL {{ ?human wdt:P140 ?religion. }}
  OPTIONAL {{ ?human wdt:P69 ?education. }}
  
  SERVICE wikibase:label {{ bd:serviceParam wikibase:language "pt-br". }}
  FILTER(?date_of_birth >= "{start_date}"^^xsd:dateTime && ?date_of_birth < "{end_date}"^^xsd:dateTime)
}}
LIMIT 8000
OFFSET {offset}"""

def get_results(endpoint_url, query):
    user_agent = "WikiMetrics Python3/%s.%s" % (sys.version_info[0], sys.version_info[1])
    sparql = SPARQLWrapper(endpoint_url, agent=user_agent)
    sparql.setQuery(query)
    sparql.setReturnFormat(JSON)
    try:
        response = sparql.query().response.read().decode("utf-8")
        clean_response = response.replace("\n", "").replace("\r", "").replace("\t", "")  # Remover caracteres de controle
        return json.loads(clean_response)
    except json.JSONDecodeError as e:
        print("Erro ao decodificar JSON após limpeza:", e)
        raise

def group_attributes(data):
    grouped_data = defaultdict(lambda: {
        "humanLabel": None,
        "sex_or_genderLabel": None,
        "country_of_citizenshipLabel": None,
        "date_of_birth": None,
        "date_of_death": None,
        "professions": set(),
        "religions": set(),
        "educations": set()
    })

    for entry in data:
        human_id = entry["human"]["value"]
        grouped_data[human_id]["humanLabel"] = entry.get("humanLabel", {}).get("value")
        grouped_data[human_id]["sex_or_genderLabel"] = entry.get("sex_or_genderLabel", {}).get("value")
        grouped_data[human_id]["country_of_citizenshipLabel"] = entry.get("country_of_citizenshipLabel", {}).get("value")
        grouped_data[human_id]["date_of_birth"] = entry.get("date_of_birth", {}).get("value")
        grouped_data[human_id]["date_of_death"] = entry.get("date_of_death", {}).get("value")

        if "professionLabel" in entry:
            grouped_data[human_id]["professions"].add(entry["professionLabel"]["value"])

        if "religionLabel" in entry:
            grouped_data[human_id]["religions"].add(entry["religionLabel"]["value"])

        if "educationLabel" in entry:
            grouped_data[human_id]["educations"].add(entry["educationLabel"]["value"])

    for human_id, details in grouped_data.items():
        details["professions"] = ", ".join(details["professions"])
        details["religions"] = ", ".join(details["religions"])
        details["educations"] = ", ".join(details["educations"])

    return grouped_data

def save_grouped_data(grouped_data, output_file):
    with open(output_file, "w", encoding="utf-8") as f:
        json.dump(grouped_data, f, ensure_ascii=False, separators=(",", ":"))

    print(f"Dados do lote salvos no arquivo '{output_file}'")

def fetch_and_save_batches(endpoint_url, base_query, start_date, end_date):
    offset = 0
    batch = 1
    
    while True:
        print(f"Consultando lote {batch}, data de {start_date} até {end_date} com OFFSET {offset}...")

        query = base_query.format(start_date=start_date, end_date=end_date, offset=offset)

        output_file = f"wikidata_lote_{batch}_{start_date}_{end_date}.json"

        if os.path.exists(output_file):
            print(f"Lote {batch} já existe. Pulando esse intervalo de datas.")
        else:
            results = get_results(endpoint_url, query)

            if not results["results"]["bindings"]:
                print("Nenhum resultado restante para esse intervalo de datas.")
                break

            grouped_data = group_attributes(results["results"]["bindings"])  # Processa os dados aqui
            print(f"Lote {batch} salvo com {len(results['results']['bindings'])} registros.")


            if len(results["results"]["bindings"]) < 8000:
                print("Último lote com menos de 8000 resultados. Finalizando.")
                save_grouped_data(grouped_data, output_file)  # Salva os dados processados
                break

            save_grouped_data(grouped_data, output_file)  # Salva os dados processados

            offset += 8000  
            batch += 1

        time.sleep(15)

    print("Processamento concluído!")

#start_date = "1646-01-01"
#end_date = "1855-01-01"
start_date = "1984-11-30"
end_date = "1994-11-28"
current_date = datetime.now()
count_queries = 1;
addition = 2;

while datetime.strptime(end_date, "%Y-%m-%d") < current_date:
    print(f"\nQuery número {count_queries}")
    fetch_and_save_batches(endpoint_url, base_query, start_date, end_date)

    start_date = end_date;
    end_date_obj = datetime.strptime(end_date, "%Y-%m-%d")
    end_date_obj += timedelta(days=10*365)
    end_date = end_date_obj.strftime("%Y-%m-%d")
    time.sleep(20 + addition)
    addition += 2
    count_queries += 1
    
