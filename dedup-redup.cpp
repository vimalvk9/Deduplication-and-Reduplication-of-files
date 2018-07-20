#include <bits/stdc++.h>
using namespace std;

/* Global variables and definitions begin */

const int CHUNK_SIZE = 10;

// Information about the actual chunk:

struct pos_and_size {
  size_t pos;
  size_t size;
};

/* END HERE */

// Function declarations

void deduplication(string inpath, string outpath);
void reduplication(string inpath, string outpath);

// Function definition

void deduplication(string inpath, string outpath)
{
	ifstream file_in(inpath,ifstream::binary);
	ofstream file_out(outpath,ifstream::binary);

	if(!file_in)
	{
		cerr << "Error while opening file_in: " << inpath << "\n";
		exit(1);
	}

	if(!file_out)
	{
		cerr << "Error while opening file_in: " << inpath << "\n";
		exit(1);
	}

	// Points to the last index of the character in the file
	file_in.seekg(0,file_in.end);

	// Last index means the size of the file as it starts from 0
	size_t total_size = file_in.tellg();
	//cout << "total size : " << total_size << "\n"; 
	size_t chunk_size = CHUNK_SIZE;
	size_t total_chunks = total_size / chunk_size;	
	size_t last_chunk_size = total_size % chunk_size;

	//cout << "Total chunk : " << total_chunks << "\n";
	//cout << "Last chunk size : " << last_chunk_size << "\n";

	if(last_chunk_size != 0)
		++total_chunks;
	else
		last_chunk_size = chunk_size;

	// Looping the file in chunks

	file_in.seekg(0,file_in.beg);
	
	size_t chunk; 
	size_t this_chunk_size;
	size_t start_of_chunk;
	map<size_t, list<pos_and_size> > dedupmap;

	for(chunk = 0; chunk < total_chunks; chunk++)
	{
		if(chunk == total_chunks-1)
		 this_chunk_size = last_chunk_size;
		else
		 this_chunk_size = chunk_size;

	 	start_of_chunk = chunk * chunk_size;
		 	
	 	list<pos_and_size> l;
	 	pos_and_size ps;
	 	
	 	vector <char> chunk_data(this_chunk_size);
	 	file_in.read(&chunk_data[0],this_chunk_size);
	 	
	 	// Hash calculation
		
		unsigned int hash = 0;
		unsigned int c;

		for(c=0;c<chunk_data.size();c++)
			hash += int(chunk_data[c]); 
		
		l = dedupmap[hash];
		ps.pos = start_of_chunk;
		ps.size = this_chunk_size;

		l.push_back(ps);
		dedupmap[hash] = l;	 
	}


		map < size_t, list<pos_and_size> > :: iterator it;

		char data[CHUNK_SIZE];
		int l_chunk_pos = 0;
		int l_chunk_size = 0;

		for(const auto it : dedupmap)
		{
			list <pos_and_size> l;
			l = (it).second;

			bool once = false;	

			list<pos_and_size> :: iterator itr;
			for(itr=l.begin();itr!=l.end();itr++)
			{
				l_chunk_size = (*itr).size;
				l_chunk_pos = (*itr).pos;
				
				if(!once)
				{
					once = true;
					file_out << l.size() << "\n"; 
					file_out << l_chunk_size << "\n";
					file_in.seekg(l_chunk_pos,file_in.beg);
					file_in.read(data,l_chunk_size);
					file_out.write(data,l_chunk_size);
				}
				file_out << l_chunk_pos << "\n";
			}
		}
}

void reduplication(string inpath,string outpath)
{
	ifstream file_in(inpath, ifstream::binary);
  	ofstream file_out(outpath, ifstream::binary);

  if (!file_in) {
    cerr << "error while opening file_in: " << inpath << endl;
    exit(1);
  }

  if (!file_out) {
    cerr << "error while opening file_out: " << inpath << endl;
    exit(1);
  }

  char line[64];
  char data[CHUNK_SIZE];
  size_t count = 0;
  size_t pos = 0;
  size_t size = 0;

  while (file_in) {
    file_in.getline(line, 64);
    count = atof(line);
    //cout <<"Line : " << line << "\n" << "Count : " << count << "\n";
    if (count <= 0) {
      break;
    }
    file_in.getline(line, 64);
    size = atoi(line);
    cout << line << " : " << size << "\n";
    memset(data, 0, 64);
    file_in.read(data, size);

    while (count--) {
      file_in.getline(line, 64);
      pos = atoi(line);

      file_out.seekp(pos, file_in.beg);
      file_out.write(data, size);
    }
  }
}

int main()
{
	deduplication("./file.in", "./file.out");
	reduplication("./file.out", "./file.re");
}