#ifndef SVNDUMP_H_
#define SVNDUMP_H_

int svndump_init(const char *filename, const char *dst_ref, int report_fileno);
void svndump_read(const char *url);
void svndump_deinit(void);
void svndump_reset(void);

#endif
