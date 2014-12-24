#include <string.h>
#include <stdlib.h> 
#include <errors.h>
#include <iostream>

#define BUF_SIZE 1024


class Buffer {
	char * buffers[1024];
	int nbuf;
	int m_ibuffer;

	char * pointers[1024];
	int npointers;

	int m_len; // < nbuf * BUF_PIECE
	int m_capacity; // = nbuf * BUF_PIECE
	int out_handle;

	int __allocate(int n)
	{
		int m = n / BUF_SIZE + (n % BUF_SIZE ? 1 : 0);
		std::cout << "MALLOC (" << m * BUF_SIZE << ")" << std::endl;
		int ibuf = nbuf;
		pointers[npointers++] = buffers[nbuf++] = (char *) malloc (m * BUF_SIZE);
		if (buffers[ibuf]) {
			for (int i = 1; i < m; i++)
				buffers[nbuf++] = buffers[ibuf] + i * BUF_SIZE;
			m_capacity += m * BUF_SIZE;
			return BUF_OK;
		}
		return BUF_ERR;
	}

	int init (int n)
	{
		int res;
		m_len = 0;
		m_capacity = 0;
		out_handle = 0;

		npointers = 0;
		m_ibuffer = 0;
		nbuf = 0;

		if (!(res = __allocate(n)))
			m_ibuffer = 0;
		return res;
	};

	int init (const char *buf, int n, int size)
	{
		init(size);
		if (m_capacity == size) {
			strncpy(buffers[0], buf, n);
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
			return __allocate(n - m_capacity);

		return BUF_OK;
	}

	int __copy(const char * buf, const int __n, int ibuf, int shift) // Copy data into the buffer, growing the underlying buffer if necessary
	{
		if (!reinit((!ibuf && !shift) ? __n : m_len + __n)) {
			int i = 0;
			int n = __n;
			while (n) {
				int m = BUF_SIZE < n ? BUF_SIZE : n;
				strncpy(buffers[ibuf] + shift, buf + i, m);
				i += m;
				n -= m;
				ibuf++;
			}
			m_ibuffer = ibuf;
			m_len += __n;
			return BUF_OK;
		}
		return BUF_ERR;
	};


public:
	Buffer(): m_len(0), m_capacity(0), out_handle(0), npointers(0), m_ibuffer(0), nbuf(0){}; //Allocate an empty buffer.
	~Buffer() {
		for (int i = 0; i < npointers; i++){
			if (pointers[i] && !out_handle) {
				std::cout << "FREE " << std::endl;
				free (pointers[i]);
			}
			pointers[i] = NULL;
		}
	};
	Buffer (int n) { // Allocate a buffer 'n' bytes long.
		init (n);
	};
	Buffer (int n, int size) { // Allocate a buffer 'n' bytes long. to grow without reallocation to 1024 bytes.
		if (!init (size)) {
			memset(buffers[0], 0, n);
			m_len = n;
		}
	};
	Buffer (const char *buf, int n) { // Allocate a buffer 'n' bytes long and copy the  data.
		if (!init(n)) {
		    strncpy(buffers[0], buf, n);
		    m_len = n;
		}
	};
	Buffer (const char *buf, int n, int size) { // Allocate a buffer 'n' bytes long and 
	// with m_capacity to grow without reallocation to 5*1024 bytes. Copy the date over.
		init(buf, n, size);
	};
	Buffer (char *buf, int n, int size, bool fl) { // Assume ownership of the buffer with
	// size 'n' (second argument) and capacity 'n' (third argument).
		out_handle = fl;
		if (fl) {
			buffers[0] = buf;
			m_len = n;
			m_capacity = size;
		}
		else
			init(buf, n, size);
	};

	int copy(const char * buf, const int n) // Copy data into the buffer, growing the underlying buffer if necessary
	{
		return __copy(buf, n, 0, 0); // Copy data into the buffer, growing the underlying buffer if necessary
	};

	int size () const { return m_len; };
	void size (int n) {
		if (!reinit(n))
			m_len = n;
	};
	char * data() { return buffers[0]; };
	int append (const char *buf, int n) { // Append the data to the buffer.
		return __copy(buf, n, m_ibuffer, m_len); // Copy data into the buffer, growing the underlying buffer if necessary
	};
	int capacity () const {return m_capacity; };
	int capacity (int n)  { // Make sure the buffer has this capacity.
		return reinit(n);
	};
};

