#include <bits/stdc++.h>
using namespace std;

int main()
{
	unordered_map<string,int>symptoms;
	vector<vector<string>> patients;
	vector<string> data;
	string s;
	ifstream file("patientjourneyfinder.csv");
	while(getline(file,s)){
		data.push_back(s);
	}
	for(string i:data){
		string str="";
		vector<string>temp;
		for(int j=0;j<i.length();j++){
			if(i[j]==','){
				temp.push_back(str);
				str="";
				continue;
			}
			str+=i[j];
		}
		patients.push_back(temp);
	}
	patients.erase(patients.begin());
	ifstream sy("symptoms.csv");
	s="";
	vector<string>sysrare;
	while(getline(sy,s)){
		sysrare.push_back(s);
	}
	sysrare.erase(sysrare.begin());
	for(string i:sysrare)if(symptoms.find(i)==symptoms.end())symptoms[i]=1;
	//storing the physician name across every patients.
	unordered_map<string,string> hashedphysician;
	vector<vector<string>> hashedpatient;
	vector<pair<int,string>> patientNameLikelihood;
	for(int i=0;i<patients.size();i++){
		vector<string> temp;
		temp.push_back(patients[i][0]);
		hashedphysician[patients[i][0]]=patients[i][12];
		for(int j=13;j<=27;j++)temp.push_back(patients[i][j]);
		hashedpatient.push_back(temp);
	}
	/**
	* calculating likelihood
	*
	*/
	for(int i=0;i<hashedpatient.size();i++){
		string name=hashedpatient[i][0];
		int count=0;
		for(int j=1;j<hashedpatient[i].size();j++){
			if(symptoms[hashedpatient[i][j]]){
				count++;
			}
		}
		patientNameLikelihood.push_back(make_pair(count,name));
	}
	sort(patientNameLikelihood.begin(),patientNameLikelihood.end());
	reverse(patientNameLikelihood.begin(),patientNameLikelihood.end());
	//
	// through physician
	unordered_map<string,int> doctor;
	unordered_map<string,int> doctorcount;
	for(int i=0;i<patientNameLikelihood.size();i++){
		if(doctor.find(hashedphysician[patientNameLikelihood[i].second])==doctor.end()){
			doctor[hashedphysician[patientNameLikelihood[i].second]]=patientNameLikelihood[i].first;
			doctorcount[hashedphysician[patientNameLikelihood[i].second]]=1;
		}
		else{
			doctorcount[hashedphysician[patientNameLikelihood[i].second]]=1;
		 	doctor[hashedphysician[patientNameLikelihood[i].second]]+=patientNameLikelihood[i].first;
		 }
	}

	/*likelihod through physician side*/
	vector<pair<double,string>>doc;
	auto it=doctor.begin();
	auto iit=doctorcount.begin();
	while(it!=doctor.end()){
		doc.push_back(make_pair((double)it->second/(double)iit->second,it->first));
		it++;
		iit++;
	}

	sort(doc.begin(),doc.end());
	reverse(doc.begin(),doc.end());
	/*List through patients side*/
	vector<string> physician;
	for(int i=0;i<patientNameLikelihood.size();i++){
		if(patientNameLikelihood[i].first>0){
			physician.push_back(hashedphysician[patientNameLikelihood[i].second]);
		}
	}
	/*List through doctor side*/
	vector<string>doctorname;
	for(int i=0;i<doc.size();i++){
		if(doc[i].first>0)
			doctorname.push_back(doc[i].second);
	}

	// for(string i:doctorname)cout<<i<<endl;                                     ----------------------------------------------------------------
	//physicianslist is a list of a physician
	unordered_map<string,bool> phy;
	int number=0;
	vector<string> physicianslist;
	cout<<"\nPhysician Id's\n\n";
	for(int i=0;i<physician.size();i++){
		if(phy.find(physician[i])==phy.end()){
			physicianslist.push_back(physician[i]);
			number++;
			phy[physician[i]]=true;
		}
	}
	for(string i:doctorname){
		if(phy.find(i)==phy.end()){
			physicianslist.push_back(i);
			number++;
			phy[i]=true;
		}
	}
	/*
	doctor details
	hard code right now;

	*/
	vector<vector<string>>doctorDetail;
	vector<string>tempDocDetail;
	ifstream doctorlist("doctorlist.csv");
	string s1="";
	while(getline(doctorlist,s1)){
		tempDocDetail.push_back(s1);
	}
	for(string i:tempDocDetail){
		string str="";
		vector<string>temp;
		for(int j=0;j<i.length();j++){
			if(i[j]=='\t'){
				temp.push_back(str);
				str="";
				continue;
			}
			str+=i[j];
		}
		temp.push_back(str);
		doctorDetail.push_back(temp);
	}
	unordered_map<string,vector<string>> hasheddoctordetail;
	for(int i=0;i<doctorDetail.size();i++){
		for(int j=1;j<doctorDetail[i].size();j++){
			hasheddoctordetail[doctorDetail[i][0]].push_back(doctorDetail[i][j]);
		}
	}
		/*

		*/
	for(string i:physicianslist){
		cout<<i<<endl;
		vector<string> details;
		details=hasheddoctordetail[i];
		for(string j:details)cout<<j<<"\t";
		cout<<endl<<endl;
	}
	cout<<"\nNumber of physician treating rare disease:\t"<<number<<endl;
	return 0;
}