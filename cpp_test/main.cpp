#include <iostream>
#include <Buffer.h>
#include <string.h>

using namespace std;

int main() {
	const char* buf = "Hello world!!!";
	char buf1[] = "Hello world!!!";
	size_t n = strlen(buf);
	size_t c = 0;

	Buffer b;
	b.copy (buf, n);
	cout << "vectos size " << b.size () << " Should be "<< n << " Capacity " << b.capacity() << endl;
	cout << "vectos: #" << b.data() << endl;
	cout << "---------------------------------------" << endl;

	Buffer b1 (n); // Allocate a buffer 'n' bytes long.
	memcpy (b1.data (), buf, n);
	cout << "vectos size " << b1.size() << " Should be "<< n <<" Capacity " << b1.capacity() <<  endl;
	cout << "vectos: " << b1.data() << endl;
	cout << "---------------------------------------" << endl;
	
	Buffer b2 (0, 1024); // Allocate a buffer 0 bytes long with capacity
	// to grow without reallocation to 1024 bytes.

	b2.size (n); // increase buffer
#ifndef EX
	memcpy (b2.data (), buf, n);
#endif
	cout << "vectos size " << b2.size () << " Should be "<< n << " Capacity " << b2.capacity() << endl;
	cout << "vectos: " << b2.data() << endl;;
	cout << "---------------------------------------" << endl;

	Buffer b3 (1024, 5 * 1024); // Allocate a buffer 1024 bytes long with
	// capacity to grow without reallocation to 
	// 5*1024 bytes.
#ifndef EX
	memset (b3.data (), 0, 1024);
#endif
	cout << "vectos size " << b3.size () << " Should be "<< 1024 << " Capacity " << b3.capacity() << endl;
	cout << "vectos: " << b3.data() << endl;
	for (int i = 0; i < 5; ++i) {
		b3.append (buf, n); // Append the data to the buffer.
		cout << "vectos size " << b3.size () << " Should be "<< 1024 + (i + 1)*n << " Capacity " << b3.capacity() << endl;
	}
	if (b3.capacity () < 10 * 1024)
		b3.capacity (10 * 1024); // Make sure the buffer has this capacity.

	cout << "vectos size " << b3.size () << " Should be "<< 1024 + 5*n << " Capacity " << b3.capacity() << endl;
	cout << "vectos: " << b3.data() << endl;
	cout << "---------------------------------------" << endl;

	Buffer b4 (buf, n); // Allocate a buffer 'n' bytes long and copy the
	// data.

	cout << "vectos size " << b4.size () << " Should be "<< n << " Capacity " << b4.capacity() << endl;
	cout << "vectos: " << b4.data() << endl;
	cout << "---------------------------------------" << endl;

	Buffer b5 (buf, n, 5 * 1024); // Allocate a buffer 'n' bytes long and 
	// with capacity to grow without 
	// reallocation to 5*1024 bytes. Copy
	// the date over.
	cout << "vectos size " << b5.size () << " Should be "<< n << " Capacity " << b5.capacity() << endl;
	cout << "vectos: " << b5.data() << endl;
	cout << "---------------------------------------" << endl;

	Buffer b6 (buf1, n, n, true); // Assume ownership of the buffer with
	// size 'n' (second argument) and capacity 
	// 'n' (third argument).
	cout << "vectos size " << b6.size () << " Should be "<< n << " Capacity " << b6.capacity() << endl;
	cout << "vectos: " << b6.data() << endl;
	cout << "---------------------------------------" << endl;

}
