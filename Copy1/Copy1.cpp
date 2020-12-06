
#include <fstream>
#include <iostream>
using namespace std;

struct BytesArray
{
	size_t size = 0;
	char* data = nullptr;
};

int k = 100000;

void AddBytes(BytesArray* array, char* bytes, int l)
{
	int a;
	if (array->size == 0)
	{
		array->data = new char[l];
		for (size_t i = 0; i < l; i++)
		{
			array->data[i] = bytes[i];
		}

		array->size += l;
	}
	else
	{
		char* tmp = new char[array->size + l];

		for (size_t counter = 0; counter < l; counter++)
			tmp[array->size + counter] = bytes[counter];
		for (size_t i = 0; i < array->size; i++)
		{
			tmp[i] = array->data[i];
		}

		delete[] array->data;

		array->data = tmp;
		array->size += l;
	}
	
}
char getElement(BytesArray* array, size_t index)
{
	if (array == nullptr || array->size < index)
	{
		exit(1);
	}
	else
			return array->data[index];
	
}
void WriteBytes(BytesArray* array, char* next)
{
	fstream dstfs;
	dstfs.open(next, ios_base::app | ios_base::binary);
	for (size_t i = 0; i < array->size; i++)
	{
		dstfs.put(getElement(array, i));
	}
	
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc < 3)
	{
		cout << "Недостаточно аргументов!";
		exit(1);
	}
	char* cur;
	char* next;
	cur = argv[1];
	next = argv[2];
	fstream srcfs;
	srcfs.open(cur, ios_base::in | ios_base::binary);
	fstream dstfs;
	dstfs.open(next, ios_base::out | ios_base::trunc | ios_base::binary);
	dstfs.close();
	if (srcfs.is_open())
	{
		BytesArray* arr = new BytesArray;
		int size = 1;
		int count = 0;
		srcfs.seekg(0, ios_base::end);
		int sizef = srcfs.tellg();
		srcfs.seekg(0);
		
		while (!srcfs.eof())
		{
			char* buffer = new char[k];
			if (0 <= sizef - count && sizef - count <= k)
			{
				srcfs.read(buffer, sizef - count+1);
				AddBytes(arr, buffer, sizef - count);
			}
			else
			{
				srcfs.read(buffer, k);
				AddBytes(arr, buffer, k);
			}
			
			count += k;
		}
		WriteBytes(arr, next);

		delete arr;
		srcfs.close();
		dstfs.close();

		return 0;
	}
	else
	{
		cout <<  "File isnt open";
	}
	return 1;
}
