#pragma once
#include <Python.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <map>
#include <set>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

class Crawling
{
private:
	PyObject *pName, *pModule, *pFunc;
	PyObject *pValue;
	std::map< std::string, int > crawlingData;
	std::thread thread;
public:
	void Print()
	{
		typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
		Comparator compFunctor = [](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2)
		{
			return elem1.second > elem2.second;
		};

		std::set<std::pair<std::string, int>, Comparator> setOfWords(
			crawlingData.begin(), crawlingData.end(), compFunctor);

		int size = setOfWords.size() * 0.3;

		int i = 0;
		for (auto it = setOfWords.cbegin(); it != setOfWords.cend(), i < size; ++it, ++i)
		{
			if (it->second >= 40)
			{
				std::cout << "key : " << it->first << " " << "value : " << it->second << '\n';
			}			
		}		
	}
	void Init()
	{
		Py_Initialize();
		pName = PyUnicode_DecodeFSDefault("crawling");		

		pModule = PyImport_Import(pName);
		Py_DECREF(pName);

		if (pModule == NULL) {
			PyErr_Print();
			fprintf(stderr, "Failed to load \"%s\"\n", "crawling");
		}
		else
		{
			std::cout << "Reading Sucess crawling.py" << std::endl;
		}
		pFunc = PyObject_GetAttrString(pModule, "Test");

		if (pFunc && PyCallable_Check(pFunc)) {
			std::cout << "Reading Sucess Test Function" << std::endl;
		}
		else
		{
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", "Test");
		}
	}

	void FindTextFromImg()
	{
		if (!std::experimental::filesystem::exists("./result/copy_0.png"))
		{
			return;
		}
		if (pFunc && PyCallable_Check(pFunc)) {
			pValue = PyObject_CallObject(pFunc, NULL);
			int count = (int)PyList_Size(pValue);
			
			PyObject *ptemp, *objectsRepresentation;

			std::vector<std::string> test;
			for (int i = 0; i < count; i++)
			{
				ptemp = PyList_GetItem(pValue, i);
				objectsRepresentation = PyObject_Repr(ptemp);
				PyObject* pyStr = PyUnicode_AsEncodedString(objectsRepresentation, "mbcs", "strict");

				test.push_back(std::string(PyBytes_AS_STRING(pyStr)));
				Py_XDECREF(objectsRepresentation);
				Py_XDECREF(pyStr);
			}
			std::vector<std::string> name;
			std::vector<int> cnt;

			int testSize = test.size();
			
			for (int s = 0; s < testSize / 2; ++s)
			{				
				name.push_back(test[s].substr(1, test[s].size() - 2));
			}
			
			for (int s = testSize / 2; s < testSize; ++s)
			{				
				cnt.push_back(stoi(test[s].substr(1, test[s].size() - 2)));
			}
			
			for (int s = 0; s < testSize / 2; ++s)
			{
				if (crawlingData.find(name[s]) == crawlingData.end())
				{					
					crawlingData.insert(make_pair(name[s], cnt[s]));
				}
				else
				{
					crawlingData[name[s]] += cnt[s];
				}
			}			
		}
	}

	void run() {
		stop();
		thread = std::thread{ &Crawling::FindTextFromImg, this};
	}

	inline void join() { if (thread.joinable()) thread.join(); };
	inline void stop() {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (thread.joinable()) {
			thread.join();
		}
	}
};