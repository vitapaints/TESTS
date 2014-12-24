#include <iostream>

using namespace std;

class Buffer {
	vector<char> buffer;
public:
	Buffer() : {}; //Allocate an empty buffer.
	~Buffer() {
	};
	Buffer (int n) { // Allocate a buffer 'n' bytes long.
		buffer(n);
	};
	Buffer (int n, int size) { // Allocate a buffer 'n' bytes long. to grow without reallocation to 1024 bytes.
		buffer(n);
		buffer.reserve (size);
	};
	Buffer (char *buf, int n) { // Allocate a buffer 'n' bytes long and copy the  data.
		buffer (buf, buf + n);
	}
	Buffer (char *buf, int n, int size) { // Allocate a buffer 'n' bytes long and 
	// with capacity to grow without reallocation to 5*1024 bytes. Copy the date over.
		buffer(buf, buf + n);
		buffer.reserve(size);
	}
	Buffer (char *buf, int n, int size, bool fl) { // Assume ownership of the buffer with
	// size 'n' (second argument) and capacity 'n' (third argument).
		buffer(n);
		buffer.reserve(size);
		bufffer.push_back(move(buf));
	}
	void copy(const char * buf, const int n) // Copy data into the buffer, growing the underlying buffer if necessary
	{
		buffer.assign(buf, buf + n);
	}
	int size () { return buffer.size(); }
	char * data() { return buffer.data(); }
	int append (char *buf, int n) { // Append the data to the buffer.
		buffer.insert(buffer.end(), buf, n);
	}
	int capacity () {return buffer.capacity(); }
	bool capacity (int n) { // Make sure the buffer has this capacity.
		return (n >= buffer.capacity());
	}



