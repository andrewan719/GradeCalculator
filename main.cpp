#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Course {
  string Course = "";
  int Credit = 0;
  int Score = 0;
  int Grade = 0;
};

struct Student {
  int ID = 0;
  string Name = "";
  vector<Course> vecCourse;
};

int isInVector(vector<Student> *vec, int target) {
  int size = (*vec).size();
  int i = 0;
  if (size == 0) {
    return -1;
  }
  while (i < (size)) {
    if ((*vec)[i].ID == target)
      return i;
    i++;
  }
  return -1;
}

double calculateGPA(vector<Course> *vec) {
  // initialize variables + find size of vector
  int size = (*vec).size();
  double GPA = 0;
  int creditHours = 0;

  for (int i = 0; i < size; i++) {
    // add grades and credit hours to total
    creditHours = creditHours + (*vec)[i].Credit;
    GPA = GPA + ((*vec)[i].Grade * (*vec)[i].Credit);
  }
  GPA = GPA / creditHours;
  return GPA;
}

void listReport(vector<Student> *vec, int location) {
  // edge case: i is not in range
  int size = (*vec).size();
  if (location > (size - 1)) {
    return;
  }
  double GPA = calculateGPA(&((*vec)[location].vecCourse));

  // Top line: print ID and Name
  cout << (*vec)[location].ID << "   " << (*vec)[location].Name << endl;
  cout << "========================" << endl;
  for (int ii = 0; ii < (*vec)[location].vecCourse.size(); ii++) {
    // Middle section: list all courses and grades
    cout << (*vec)[location].vecCourse[ii].Course << "   "
         << (*vec)[location].vecCourse[ii].Credit << "   "
         << (*vec)[location].vecCourse[ii].Score << "   "
         << (*vec)[location].vecCourse[ii].Grade << endl;
  }
  cout << "========================" << endl;
  // Bottom line: print GPA
  cout << "Total GPA: " << GPA << endl << endl << endl;
}

int main() {
  fstream inputFile;
  string fileName = "StudentRecords.txt";
  string token;

  vector<Student> vecStu;
  inputFile.open(fileName, ios::in);

  if (inputFile.is_open()) {
    int index = 0;
    int ID;
    string Name;
    string CourseName;
    int Credit;
    int Score;
    int Grade;
    while (!inputFile.eof()) {
      inputFile >> ID >> Name >> CourseName >> Credit >> Score;
      // Determine grade, remove any above 100 scores
      Grade = (Score - 50) / 10;
      if (Grade > 4) {
        Grade = 4;
      }
      int ii = isInVector(&vecStu, ID);
      if (ii == -1) { // The student record does not exist
        Course newCourse = {CourseName, Credit, Score, Grade};
        Student newStudent = {ID, Name};
        vecStu.push_back(newStudent);
        vecStu[index].vecCourse.push_back(newCourse);
        index++;
      } 
      else { /// The student exists
        Course newCourse = {CourseName, Credit, Score, Grade};
        vecStu[ii].vecCourse.push_back(newCourse);
      }
    }

    inputFile.close();
    //Display records for every student in vector
    int size = (vecStu).size();
    for (int i = 0; i < size; i++) {
      listReport(&vecStu, i);
    }
  } else
    cout << "File cannot be opened.";
  return 0;
}
