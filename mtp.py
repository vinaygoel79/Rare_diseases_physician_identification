import csv
import time
t1=time.time()
patients = []
with open('patientjourneyfinder.csv','r') as f: 
	reader = csv.reader(f)
	for row in reader: patients.append(row)
patients = patients[1:]
# print len(patients)
sysrare = []
with open('symptoms.csv','r') as f:
	reader = csv.reader(f) 
	for row in reader: sysrare.append(row[0])
symptoms = { x:1 for x in set(sysrare[1:]) }

hashedpatients,hashedphysician = [([x[0]]+x[13:28]) for x in patients], { x[0]:x[12] for x in patients }
patientNameLikelihood = (sorted([(sum([1 for x in patient[1:] if x in symptoms]),patient[0]) for patient in hashedpatients]))[::-1]

doctors,doctorCount = {},{}
for patient in patientNameLikelihood:
	if hashedphysician[patient[1]] in doctors:
		doctors[hashedphysician[patient[1]]] += patient[0]
		doctorCount[hashedphysician[patient[1]]] += 1
	else:
		doctors[hashedphysician[patient[1]]] = patient[0]
		doctorCount[hashedphysician[patient[1]]] = 1

doc = []
for k,v in doctors.iteritems(): doc.append((float(doctors[k])/float(doctorCount[k]),k))
doc = (sorted(doc))[::-1]

physicians,doctorName = [hashedphysician[x[1]] for x in patientNameLikelihood if x[0]>0],[x[1] for x in doc if x[0]>0]
phy,number,physiciansList = {},0,[]

for physician in physicians:
	if not(physician in phy):
		physiciansList.append(physician)
		phy[physician] = True
		number += 1
for doctor in doctorName:
	if not(doctor in phy):
		number += 1
		physiciansList.append(doctor)
		phy[doctor] = True

doctorDetail = []
with open("doctorlist.csv",'r') as f:
	reader = csv.reader(f)
	for row in reader: doctorDetail.append(row[0].split('\t'))

hashedDoctorDetail = {}
for d in doctorDetail: hashedDoctorDetail[d[0]] = d[1:]
t2=time.time()
for i in physiciansList:
	print i
	print "\t".join(hashedDoctorDetail[i])

print "\nNumber of physician treating rare disease:",number

print t2-t1
