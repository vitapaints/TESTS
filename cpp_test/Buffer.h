#include <string.h>
#include <stdlib.h> 
#include <errors.h>
#include <iostream>

class Buffer {
	char * buffer;
	int m_len;
	int m_capacity;
	int out_handle;

	int init (int n)
	{
		m_len = 0;
		m_capacity = 0;
		buffer = NULL;
		out_handle = 0;
		std::cout << "MALLOC (" << n << ")" << std::endl;
		buffer = (char*) malloc (n);
		if (buffer) {
			m_len = n;
			m_capacity = n;
			return BUF_OK;
		}
		return BUF_ERR;
	};

	int init (const char *buf, int n, int size)
	{
		init(size);
		if (m_len == size) {
			strncpy(buffer, buf, n);
			m_len = n;
			return BUF_OK;
		}
		return BUF_ERR;
	};

	int reinit(int n)
	{
		if (out_handle) {
			std::cout << "ERR: OUTER BUFFER!" << std::endl;
			return BUF_ERR;
		}
		if (m_capacity < n)
		{
			buffer = (char *)realloc(buffer, n);
			std::cout << "REALLOC (" << n << ")" << std::endl;
			if (buffer)
				m_capacity = n;
			else {
				m_capacity = 0;
				m_len = 0;
				return BUF_ERR;
			}
		}
		return BUF_OK;
	}

public:
	Buffer(): m_len(0), m_capacity(0), buffer(NULL), out_handle(0) {}; //Allocate an empty buffer.
	~Buffer() {
		if (buffer && !out_handle) { 
			std::cout << "FREE " << std::endl; 
			free (buffer);
		}
		buffer = NULL;
	};
	Buffer (int n) { // Allocate a buffer 'n' bytes long.
		init (n);
	};
	Buffer (int n, int size) { // Allocate a buffer 'n' bytes long. to grow without reallocation to 1024 bytes.
		if (!init (size)) {
			memset(buffer, 0, n);
			m_len = n;
		}
	};
	Buffer (const char *buf, int n) { // Allocate a buffer 'n' bytes long and copy the  data.
		if (!init(n))
		    strncpy(buffer, buf, n);
	};
	Buffer (const char *buf, int n, int size) { // Allocate a buffer 'n' bytes long and 
	// with m_capacity to grow without reallocation to 5*1024 bytes. Copy the date over.
		init(buf, n, size);
	};
	Buffer (char *buf, int n, int size, bool fl) { // Assume ownership of the buffer with
	// size 'n' (second argument) and capacity 'n' (third argument).
		out_handle = fl;
		if (fl) {
			buffer = buf;
			m_len = n;
			m_capacity = size;
		}
		else
			init(buf, n, size);
	};
	int copy(const char * buf, const int n) // Copy data into the buffer, growing the underlying buffer if necessary
	{
		if (!reinit(n)) {
			strncpy(buffer, buf, n);
			m_len = n;
			return BUF_OK;
		}
		return BUF_ERR;
	};
	int size () const { return m_len; };
	void size (int n) { 
		if (!reinit(n))
			m_len = n;
	};
	char * data() { return buffer; };
	int append (const char *buf, int n) { // Append the data to the buffer.
		if (!reinit(m_len + n)) {
			strncpy(buffer + m_len, buf, n);
			m_len += n;
			return BUF_OK;
		}
		return BUF_ERR;
	};
	int capacity () const {return m_capacity; };
	int capacity (int n)  { // Make sure the buffer has this capacity.
		return reinit(n);
	};
};
