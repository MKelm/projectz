#include "json.hpp"

Json::Json(string p_file) {
  chunkLength = 1024;
  file = p_file;
}

int Json::load() {
  FILE *fp = fopen(file.c_str(), "r");
  if (!fp)
    return 0;

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

string Json::getToken(unsigned int index) {
  return json.substr(tokens[index].start, tokens[index].end - tokens[index].start);
}

unsigned int Json::getTokenType(unsigned int index) {
  return tokens[index].type;
}

unsigned int Json::getTokenSize(unsigned int index) {
  return tokens[index].size;
}

void Json::set(string p_json) {
  json = p_json;
}

int Json::save() {
  FILE *fp = fopen(file.c_str(), "w");
  if (!fp)
    return 0;
  fputs(json.c_str(), fp);
  fclose(fp);
  return 1;
}

void Json::unload() {
  json = "";
  free(tokens);
}
