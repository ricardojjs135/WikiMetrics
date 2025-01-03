import sys
import json
from SPARQLWrapper import SPARQLWrapper, JSON

endpoint_url = "https://query.wikidata.org/sparql"

query = """SELECT ?human ?humanLabel ?sex_or_gender ?sex_or_genderLabel ?country_of_citizenship ?country_of_citizenshipLabel ?date_of_birth ?date_of_death WHERE {
  ?human wdt:P31 wd:Q5.
  ?human wdt:P27 wd:Q155.
  OPTIONAL { ?human wdt:P21 ?sex_or_gender. }
  OPTIONAL { ?human wdt:P27 ?country_of_citizenship. }
  OPTIONAL { ?human wdt:P569 ?date_of_birth. }
  OPTIONAL { ?human wdt:P570 ?date_of_death. }
  
  SERVICE wikibase:label { bd:serviceParam wikibase:language "pt-br". }

}
LIMIT 50
OFFSET 0"""


def get_results(endpoint_url, query):
    user_agent = "WikiMetrics Python/%s.%s" % (sys.version_info[0], sys.version_info[1])
    sparql = SPARQLWrapper(endpoint_url, agent=user_agent)
    sparql.setQuery(query)
    sparql.setReturnFormat(JSON)
    return sparql.query().convert()


results = get_results(endpoint_url, query)

# Salvar os resultados em um arquivo JSON
with open("wikidata_results.json", "w", encoding="utf-8") as f:
    json.dump(results, f, ensure_ascii=False, indent=4)

print("Arquivo JSON salvo como 'wikidata_results.json'")
