#ifndef ENCODE_UTIL_H
#define ENCODE_UTIL_H

int ENCODE_UTIL_base64(const unsigned char* input_data, size_t input_length, size_t* output_length, char** output_data);

int ENCODE_UTIL_utf8_to_gbk(const char* utf8_str, char** gbk_str);

int ENCODE_UTIL_gbk_to_utf8(const char* gbk_str, char** utf8_str);

#endif // !ENCODE_UTIL_H
