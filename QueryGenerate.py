import sys
import json
import os
from SPARQLWrapper import SPARQLWrapper, JSON
from collections import defaultdict

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
}}
LIMIT 50
OFFSET {offset}"""

def get_results(endpoint_url, query):
    user_agent = "WikiMetrics Python/%s.%s" % (sys.version_info[0], sys.version_info[1])
    sparql = SPARQLWrapper(endpoint_url, agent=user_agent)
    sparql.setQuery(query)
    sparql.setReturnFormat(JSON)
    return sparql.query().convert()

def fetch_all_results(endpoint_url, base_query):
    offset = 0
    batch = 1
    all_data = []
    max_batches = 10  # Número máximo de lotes

    while batch <= max_batches:  # Apenas para testes, modificar para "while True" quando for rodar o programa
        print(f"Consultando lote {batch} com OFFSET {offset}...")
        query = base_query.format(offset=offset)
        results = get_results(endpoint_url, query)

        if not results["results"]["bindings"]: 
            print("Nenhum resultado restante.")
            break

        all_data.extend(results["results"]["bindings"])
        offset += 50  
        batch += 1    

    return all_data

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

    print(f"Dados agrupados e minimizados salvos no arquivo '{output_file}'")

data = fetch_all_results(endpoint_url, base_query)
grouped_data = group_attributes(data)
save_grouped_data(grouped_data, "wikidata_final_results.json")
