String getValue(String data, char separator, int index) {
  int found = 0;
  int str_index[] = {0, -1};
  int max_index = data.length() - 1;

  for (int i = 0; i <= max_index && found <= index; i++) {
    if (data.charAt(i) == separator || i == max_index) {
      found++;
      str_index[0] = str_index[1] + 1;
      str_index[1] = (i == max_index) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(str_index[0], str_index[1]) : "";
}