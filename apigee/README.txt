Apigee Interview Assignment

Problem statement :

Consider a person. Each person has the following attributes :

1. Name
2. Date of Birth
3. Place of Birth
4. Work Location
5. Current Location
6. High School
7. List of friends

Each person can have several friends and each friend can in turn have several friends. Given two persons, say, person1, person2 (person2 should be a friend of person1's friend), identify if the person2 can also be a friend for person1.


Input :

Input is given from a file. It contains the data for number of persons in the graph along with the details of 7 attributes (as mentioned above) for each person. Two person numbers P1 and P2 are given to check if P2 can possible be a friend of P1.

Output :

Given two person numbers P1 and P2, displays the similarity measure between P1 and P2 along with the result if they could be friends or not.

Design :

The given problem is modelled into a graph where each node represents an object of Graph class.The list of friends attribute is used to establish the links between the nodes. A given node is connected to all nodes contained in its friend list. 

The attributes of the persons are stored as objects of Person class.

For each attribute, their relative importance in establishing friendship is identified and a weight is assigned accordingly.

1. Attribute name has no importance for two persons to become friends. Hence, it is assigned a weight of 0.
2. People in same age group are more likely to be friends. Hence a weight of 1.0 is assigned to it.
   However, we cannot totally neglect as people of different age groups can also become friends. So
		if age difference less than 5
			weight = 1.0
		else if weight difference more than 5 and less than 10
			weight = 0.5
		else
			weight = 0.25

3. Place_of_birth matters to some extent as people from same location are more likely to mingle faster. So, this attribute can be weighted to 2.5. Again, totally cannot neglect the possibility of people from other locations to become friends, so assuming that there is 25% chance for them to become friends, the weight is 0.625 for persons from different locations.

4. If the work_location are same, the chance of being friends is high. They could work in same office or live in same locality. Hence this attribute is assigned a weight of 3. Again, we cannot totally neglect the possibility of people from other work locations to become friends, so assuming that there is 25% chance for them to become friends, the weight is 0.75 for persons from different work locations.

5.Current_location slighlty has an edge over work_location, since this attribute confirms that the two persons are living in the same location at present. People with same work location may have different current locations are go there occasionally. So this attribute weights 3.5. Again, we cannot totally neglect the possibility of people from other current locations to become friends, so assuming that there is 25% chance for them to become friends, the weight is 0.875 for persons from different current locations.

6.Persons from same high_school are highly likely to be friends since school is a very localized place unlike a city, and so it weighs 5. Again, totally cannot neglect the possibility of people from other locations to become friends, so assuming that there is 25% chance for them to become friends, the weight is 1.25 for persons from different high schools.
			
7.Depending on the number of mutual friends between the two persons P1 and P2, weights can be assigned:
				if(mutual_friends_ocunt >=3)
					weight = 6.0
				else 
					weight = mutual_friends_count*2

8.To find the shortest path between the two persons, Dijkstra's algorithm is used to find the shortest path between them and based on their distance in graph, a weight of 2 is assigned if distance is less than or equal to 2 else 25% possibility is assumed and weight of 0.5 is given.

9. To identify the mutual friend (or parent of P2) say Px, Breadth-First-Search is done on the graph.

9.To find the influence of this mutual friend on final friendship likelihood between the two given persons, the similarity measure between the person P1 and mutual friend (Px) is calculated. Then, the the similarity measure between the person P2 and mutual friend Px is calculated. 

10. These similarity measures are together combined to find the final friendship likelihood.

11. Final Friendship Likelihood = Total calculated similarity measure / Maximum possible similarity measure

12. if (Final Friendship Likelihood >= 0.5)
		Persons P1 and P2 can possibly be friends 
	else
		Persons P1 and P2 cannot possibly be friends


Testing:

Two files (testcase1.txt and testcase2.txt) have been given. Change the testcase file name in apigee_assignment.cpp file to run a different testcase.

Explanation of testcase file:

Line 1 - Number of persons in the graph
Line 2 - Name of person 0
Line 3 - Date of birth of person 0
Line 4 - Place of birth of person 0
Line 5 - Work Location of person 0
Line 6 - Current Location of person 0
Line 7 - High School of person 0
Line 8 - Number of friends in friend list for person 0

If say number of friends for friend list for person 0 is 3, then the next three lines (Lines 9,10,11) contain the friend numbers of person 0 with one friend number in each line.

Similarly, the process is repeated for the number of persons specified in Line 1.

Compilation and Running:

In the terminal, go to corresponding folder where the source file and testcases are contained and type: 

To complie : g++ -std=c++11 apigee_assignment.cpp -o apigee 

To run : ./apigee

