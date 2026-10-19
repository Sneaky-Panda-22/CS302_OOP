#include<iostream>
#include<string>
class Patient {
protected:
    int patientId;
    std::string name;
    int age;
    std::string contactNo;
    int lengthOfStay;
public:
    void getPatientInfo() {
        std::cout << "Enter Patient ID: ";
        std::cin >> patientId;
        std::cout << "Enter Name: ";
        std::cin >> name;
        std::cout << "Enter Age: ";
        std::cin >> age;
        while(age < 0) {
            std::cout << "Invalid age. Enter again: ";
            std::cin >> age;
        }
        std::cout << "Enter Contact Number: ";
        std::cin >> contactNo;
        std::cout << "Enter Length of Stay: ";
        std::cin >> lengthOfStay;
        while(lengthOfStay < 0) {
            std::cout << "Invalid days. Enter again: ";
            std::cin >> lengthOfStay;
        }
    }
    void displayPatient() {
        std::cout << "Patient ID: " << patientId << '\n';
        std::cout << "Name: " << name << '\n';
        std::cout << "Age: " << age << '\n';
        std::cout << "Contact: " << contactNo << '\n';
        std::cout << "Days Stayed: " << lengthOfStay << '\n';
    }
};
class MedicalRecord : public Patient {
protected:
    std::string diagnosis;
    int consultationVisits;
    float diagnosticsTestCharge;
    float consultationCharge;
    char isEmergency;
public:
    void getMedicalInfo() {
        std::cout << "Enter Diagnosis: ";
        std::cin >> diagnosis;
        std::cout << "Enter number of visits: ";
        std::cin >> consultationVisits;
        while(consultationVisits < 0) {
            std::cout << "Invalid visits. Enter again: ";
            std::cin >> consultationVisits;
        }
        std::cout << "Enter fee per visit: ";
        std::cin >> consultationCharge;
        while(consultationCharge < 0) {
            std::cout << "Invalid charge. Enter again: ";
            std::cin >> consultationCharge;
        }
        std::cout << "Enter test charges: ";
        std::cin >> diagnosticsTestCharge;
        while(diagnosticsTestCharge < 0) {
            std::cout << "Invalid charges. Enter again: ";
            std::cin >> diagnosticsTestCharge;
        }
        std::cout << "Is it emergency? (y/n): ";
        std::cin >> isEmergency;
    }
    void displayMedical() {
        std::cout << "Diagnosis: " << diagnosis << '\n';
        std::cout << "Visits: " << consultationVisits << '\n';
    }
};
class HospitalBill : public MedicalRecord {
private:
    float totalBill;
    float roomChargePerDay = 1000.0;
    float emergencyServiceCharge = 1200.0;
    float totalConsultation;
    float totalRoomRent;
    float emergencyFee = 0.0;
    float discount = 0.0;
public:
    void makeBill() {
        getPatientInfo();
        getMedicalInfo();
        totalConsultation = consultationCharge * consultationVisits;
        totalRoomRent = roomChargePerDay * lengthOfStay;
        if (isEmergency == 'y' || isEmergency == 'Y') {
            emergencyFee = emergencyServiceCharge;
        }
        totalBill = totalConsultation + diagnosticsTestCharge + totalRoomRent + emergencyFee;
        if (age > 60) {
            discount = totalBill * 0.10;
            totalBill = totalBill - discount;
        }
        std::cout << "\nHOSPITAL BILL DETAILS\n";
        displayPatient();
        displayMedical();
        std::cout << "Consultation Fee: Rs. " << totalConsultation << '\n';
        std::cout << "Test Fee: Rs. " << diagnosticsTestCharge << '\n';
        std::cout << "Room Fee: Rs. " << totalRoomRent << '\n';
        if (emergencyFee > 0) {
            std::cout << "Emergency Fee: Rs. " << emergencyFee << '\n';
        }
        if (discount > 0) {
            std::cout << "Discount: Rs. " << discount << '\n';
        }
        std::cout << "Final Total: Rs. " << totalBill << '\n';
    }
};
int main() {
    HospitalBill patientBill;
    patientBill.makeBill();
    return 0;
}
