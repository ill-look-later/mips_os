#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <inttypes.h>
#include "alloc.h"

#define FS_ERROR 0
#define FS_SUCCESS 1


/*
 * FS_REGULAR
 */
typedef struct {
	uint8_t *start;
	uint32_t size;
} fs_regular;

/*
 * FS_DIRECTORY
 */
typedef struct fs_list_cell* fs_list;

typedef struct {
	fs_list children;
} fs_directory;

/*
 * FS_FILE
 */
enum {FS_TYPE_REGULAR, FS_TYPE_DIRECTORY};

typedef struct {
	union {
		fs_regular regular;
		fs_directory directory;
	} data;
	uint8_t file_type; // REGULAR, DIRECTORY
	char * name;
} fs_file;


typedef struct fs_list_cell {
	fs_file *file;
	struct fs_list_cell *next;
} fs_list_cell;



typedef struct fs_cursor {
	fs_file *root;
	fs_file *working;
} fs_cursor;

int fs_init_directory(mem_allocator *allocator, fs_file *dir, const char *dirname);

int fs_add_file(mem_allocator *allocator, 
				fs_file *dir, 
				const char *filename, 
				fs_file **newfile);//, fs_cursor *newfile_curs);

int fs_add_dir(mem_allocator *allocator, 
				fs_file *dir, 
				const char *dirname,
				fs_file **newdir);//, fs_cursor *newdir_cursor);



//void fs_get_root_cursor(fs_file *dir);

void fs_change_directory(fs_cursor *cursor, const char *dirname);

//int fs_write_file(mem_allocator *allocator, fs_file *file, const uint8_t *data, uint32_t size);


#endif