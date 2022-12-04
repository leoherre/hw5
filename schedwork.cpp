

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
//copies of schedule() by reference 
void scheduleHelper(
  const vector<vector<bool>>& cpyofAvail,
  vector<vector<Worker_T>>& cpyofsched,
  int workerAtten [],
  int& day,
  const size_t dailyNeed,
  const size_t maxShifts,
  bool& valSched
);

bool notWorking(const Worker_T&worker, vector<vector<Worker_T>>& cpyofsched, const int& day);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
  //insert workers into avail matrix
  vector<Worker_T> temp;
  for(int i = 0; i < (int)avail.size();i++){
    sched.push_back(temp);
  }

  int size = avail[0].size();
  //initialize workersAtten [] to 0
  int workerAtten[size];
  for(int i = 0; i < size;i++){
    workerAtten[i] = 0;
  }
   
  bool validSched = false;
  int day = 0;
  scheduleHelper(avail, sched, workerAtten, day,dailyNeed,maxShifts, validSched);
  return validSched;
}

bool notWorking(const Worker_T& worker, vector<vector<Worker_T>> & schedule, const int& day){
  //0 so worker is not scheduled 
  if(schedule[day].size() == 0){
    return true;
  }
  else{
    //loop through workers 
    for(int i = 0; i < (int)schedule[day].size(); i++){
      //worker is aready booked so return false 
      if(schedule[day][i] == worker){
        return false;
      }
    }
  }
  return true;
}

void scheduleHelper(
  const vector<vector<bool>>& cpyofAvail,
  vector<vector<Worker_T>>& cpyofsched,
  int workerAtten [],
  int& day,
  const size_t dailyNeed,
  const size_t maxShifts,
  bool& valSched 
)
{
  
  for(int i = 0;i < (int) cpyofAvail[0].size();i++){
    Worker_T worker = (unsigned int) i;
    //worker is free, maxshifts not reached, worker is not working 
    if(cpyofAvail[day][i] == true && workerAtten[i] < (int) maxShifts &&
     notWorking(worker, cpyofsched, day)){
       workerAtten[i] +=1;
       cpyofsched[day].push_back(worker);
      //enough workers are reached 
       if(cpyofsched[day].size() == dailyNeed){
         //day/schedule is still valid 
         if(day < (int)cpyofAvail.size()-1){
           day +=1;
           scheduleHelper(cpyofAvail, cpyofsched, workerAtten, day, dailyNeed, maxShifts, valSched);
           if(valSched == true){
             return;
           }

           else{
             workerAtten[i] -= 1;
             day -= 1;
             cpyofsched[day].pop_back();
           }
         }
         //not valid schedule 
         else{
           valSched = true;
         }
       }
       //not enough workers, so recurse 
         else if(cpyofsched[day].size() != dailyNeed){
           scheduleHelper(cpyofAvail, cpyofsched, workerAtten, day, dailyNeed, maxShifts, valSched);
           if(valSched != false){
             return;
           }
           else{
             workerAtten[i] -= 1;
             cpyofsched[day].pop_back();
           }
         }
     }
  }
}



