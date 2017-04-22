/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/10/14
* Last Modification Date: 10/10/14
* Filename: firelaws.cpp
*
* Overview:
* This program will determine if a meeting meets the fire
* regulations code for the meeting room.
*
* Input:
* The input will be an two integers from the user. The first
* will be the max occupancy of a room. The second will be the
* number of people attending a meeting in that room.
*
* Output:
* The output for this program will be whether the meeting can
* take place in the room. In addition it will say if more
* people can attend or if some have to leave for the meeting
* to take place.
******************************************************************************/

#include <iostream>

using namespace std;

int main()
{
	int max; //user input for the max occupancy of a room
	int num; //user input for the number of people attending

	// Ask for room occupancy and number attending
	cout << "What is the max occupancy of the meeting room?" << endl;
	cin >> max;
	cout << "How many people are attending the meeting?" << endl;
	cin >> num;

	// check that max and num are positive numbers
	while (max <= 0 || num < 0)
	{
		if (max <= 0) // input error for max occupancy
		{
			cout << "\nThere cannot be a zero or negative max occupancy."
				 << "\nPlease give a positive integer:" << endl;
			cin >> max;
		}
		if (num < 0) // input error for people attending
		{
			cout << "\nThere cannot be negative people attending."
				 << "\nPlease give a positive integer:" << endl;
			cin >> num;
		}
	}

	//Display if the meeting can take place and how many more can join
	//or need to leave
	if (max >= num) // if the meeting can take place
	{
		cout << "\nYour meeting can be held here." << endl;

		if (max != num)
		{
			cout << max - num << " more"
			     << ((max - num) == 1? " person" : " people")
                 << " can join the meeting" << endl;
		}
		else
		{
			cout << "No more people can join your meeting." << endl;
		}
	}
	else // if the meeting cannot take place
	{
		cout << "\nYour meeting cannot be held here. It violates fire"
			 << " safety protocols." << endl;
		cout << num - max
             << ((num - max) == 1? " person needs" : " people need")
             << " to leave the meeting for it to be held here."
			 << endl;
	}

	return 0; //false; had no errors
}
