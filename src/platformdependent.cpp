#include <process.h>
#include <processes.h>

#include <experimental/filesystem>
#include <fstream>
#include <string.h>




/*=============================== Processes functions ===============================*/
bool IsNumerical(const std::string& path){
	bool result = true;
	for(unsigned int c=6; c<path.size(); ++c){
		if(path[c]<'0' || path[c]>'9'){
			result = false;
			break;
		}
	}
	return result;
}
#include <iostream>
void Processes::GetProcesses(){
	for(const auto& entry : std::experimental::filesystem::directory_iterator("/proc/")){
		const std::string& _path = entry.path();
		std::string path(_path.begin(), _path.end());
		if(IsNumerical(path) && std::experimental::filesystem::is_directory(path)){
			for(const auto& entry2 : std::experimental::filesystem::directory_iterator(path)){
				const std::string& __path = entry2.path();
				std::string path2(__path.begin(), __path.end());
				if(strcmp(path2.c_str()+path2.size()-5, "/stat")==0){
					std::cout<<path2<<" : ";
					std::ifstream ifs(path2);
					std::string line = "";
					std::getline(ifs, line);
					std::cout<<line<<"\n";
					ifs.close();
					processes.push_back(Process(line));
				}
				//std::string line = "";
				//while(std::getline(ifs, line)){
				//	std::cout<<line<<"\n";
				//}
				//ifs.close();
			}
		}
	}
	//processes.push_back(Process("proc/100"));
}


void Processes::GenerateMemoryProfile(Process* process){
	
}


void Processes::GenerateCPUProfile(Process* process){
	/*get number of threads*/

}


void Processes::GenerateOpenFileProfile(Process*){

}


void Processes::GenerateOpenPortProfile(Process* process){

}



/*=============================== Process functions ===============================*/
Process::Process(const std::string& proc_stat_str): status(0x0){

	//get process ID
	process_ID = 100;

	//get process name
	process_name = "place holder";
}


void Process::CleanUp(){

}
