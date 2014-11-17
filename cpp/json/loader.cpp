#include "loader.hpp"

JsonLoader::JsonLoader(string p_file) {
  chunkLength = 1024;
  file = p_file;
}

int JsonLoader::set() {
  FILE *fp = fopen(file.c_str(), "r");
  if (!fp)
    return FALSE;

  fseek(fp, 0L, SEEK_END);
  unsigned int f_size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  json = "";

  char chunk[chunkLength];
  while (fgets(chunk, chunkLength, fp) != NULL) {
    json += string(chunk);
  }
  fclose(fp);

  unsigned int r;
  jsmn_parser p;
  jsmn_init(&p);
  tokens = (jsmntok_t*)malloc(sizeof(jsmntok_t) * f_size/3);

  return jsmn_parse(&p, json.c_str(), strlen(json.c_str()), tokens, f_size/3);
}

string JsonLoader::getToken(unsigned int index) {
  return json.substr(tokens[index].start, tokens[index].end - tokens[index].start);
}

unsigned int JsonLoader::getTokenType(unsigned int index) {
  return tokens[index].type;
}

string JsonLoader::getJson() {
  return json;
}

jsmntok_t *JsonLoader::getTokens() {
  return tokens;
}

void JsonLoader::unset() {
  free(tokens);
}
