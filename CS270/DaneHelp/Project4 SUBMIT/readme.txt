//********************************
// Dane Sears
// CS270-001
// Project 4
// December 1, 2018
// 
// readme.txt
//********************************


MyCloud is designed to act as a very basic cloud storage server. With the
	client software running, the user can store, retrieve, copy and 
	delete text files at their request via the client command line.

A secret key is required for connecting to the server. This key is supplied
	to the server via a command line argument and must be matched by
	the user who attempts to connect via the client.

Mycloudserver requires two command line arguments when ran:
	./mycloudserver [port] [secret key]

Mycloudclient requires three command line arguments when ran:
	./mycloudclient [host] [port] [secret key]
	

MyCloud Basic Functions:

	COPY TEXT FILE ON CLIENT SIDE
	cp [source file] [destination file]
	
	COPY TEXT FILE ON CLOUD
	cp c:[source file] c:[destination file]

	STORE TEXT FILE ON CLOUD
	cp [source file] c:[destination file]

	RETRIEVE TEXT FILE FROM CLOUD
	cp c:[source file] [destination file]

	DELETE TEXT FILE ON CLOUD
	rm [file]

	DISPLAY FILES ON CLOUD
	ls

	QUIT
	quit


Mycloud seems to work great for the test situations that I given it. This was
	definitely the most challenging programming project that I have ever
	done and I have to say that I enjoyed the ride and am very proud of
	getting a nice working copy made. 

Enjoy!
	
