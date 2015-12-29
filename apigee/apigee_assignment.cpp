#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include <string.h>

#define MAX 32767

using namespace std;

int cnt=0;

// Graph class
class Graph 
{
    // Number of vertices in the given graph
    int no_of_vertices; 

    // Adjacency list for each node
    list <int> *adjacency_list; 

public:

    // Constructor to initialize the graph
    Graph(int v) 
    {
        no_of_vertices = v;
        adjacency_list = new list <int> [no_of_vertices];
    }           

    // Constructing edges between nodes
    void addlink(int src,int dst)
    {
        adjacency_list[src].push_back(dst); 
    }
    
    int BFS(int src,int dst)
    {
        int src1 = src;
        int dst1 = -1;

        // To keep track of visited nodes
        bool *is_visited = new bool[no_of_vertices]; 

        // Initially setting all visited nodes to 0
        for(int i=0;i<no_of_vertices;i++)
            is_visited[i] = false; 

        // Queue for BFS
        list <int> q; 

        // Source vertex (P1) is visited first. Push it into the queue
        is_visited[src1] = true; 
        q.push_back(src1); 

        list <int> :: iterator i;

        while(!q.empty())
        {
            // Dequeue the first element from queue
            src1 = q.front();
            q.pop_front();

            /* Iterate through the list until you find the destination vertex (P2)
            and break when it is found */

            for(i = adjacency_list[src1].begin(); i != adjacency_list[src1].end();++i)  
            {
                if(!is_visited[*i])
                {
                    is_visited[*i] = true;
                    cnt++;
                    if(*i == dst) 
                    {                                  
                        dst1 = *i;
                        break;
                    }
                    q.push_back(*i);
                }
            }

            // dst1 contains destination node (P2)
            if(dst1 == dst)     
                break;
        }
        // src1 contains parent of destination node (Px)
        return src1;            
    }
};

// Represents person class
class person                    
{
    public:
        // Each attribute is declared as an object of string class
        string name;           
        string dob;
        string place_of_birth;
        string work_location;
        string current_location;
        string high_school;

        // Friends list is represented as an integer list (class)
        list <int> friends_list;  

        void print()
        {
            cout <<"Person name : "<<name<<"\n";
            cout <<"Date of birth : "<<dob<<"\n";
            cout <<"Place of birth : "<<place_of_birth<<"\n";
            cout <<"Work Location : "<<work_location<<"\n";
            cout <<"Current Location : "<<current_location<<"\n";
            cout <<"High School : "<<high_school<<"\n";
            cout <<"Friends List : ";
            list <int> ::iterator i;
            for(i=friends_list.begin();i != friends_list.end();i++)
                cout <<*i <<" "; 
            cout<<"\n";
        }

};

int minDistance(int dist[], bool sptSet[],int n)
    {
       // Initialize min value
       int min = MAX, min_index;
     
       for (int v = 0; v < n; v++)
         if (sptSet[v] == false && dist[v] <= min)
             min = dist[v], min_index = v;
     
       return min_index;
    }
/* compute_mutual_friends function takes two person objects as parameters
   and calculates the number of mutual friends between them */
float compute_mutual_friends(person p1,person p2)
{

    int mutual_friends_count = 0;

    //Sort the friends_list of the two persons
    p1.friends_list.sort();
    p2.friends_list.sort();

    list <int> :: iterator i;
    list <int> :: iterator j;

    i = p1.friends_list.begin();
    j = p2.friends_list.begin();

    // Find intersection of two lists
    while( i != p1.friends_list.end() && j != p2.friends_list.end())
    {
        if( *i < *j )
            i++;
        else if( *j < *i )
            j++;
        else
        {
            j++;
            i++;
            // If an intersecting element is found, increment the mutual friends count
            mutual_friends_count++;
        }
    }

    // A maximum weight of 6.0 is given to people with atleast three mutual friends 
    if(mutual_friends_count >= 3)
        return 6.0;
    else

    // Return      
        return (mutual_friends_count*2.0);
}

/* If the two persons have the same high school, then compute_high_school
    would return a weight of 5.0 else return 25% of total weight (assumption that they can still be friends 40% of the time*/
float compute_high_school(person p1,person p2)
{
    if(p1.high_school.compare(p2.high_school) == 0)
        return 5.0;
    else
        return 0.25 * 5.0;
}

/* If the two persons have the same work location, then compute_work_location
    would return a weight of 3.0 else return 25% of total weight (assumption that they can still be friends 40% of the time*/
float compute_work_location(person p1,person p2)
{
    if(p1.work_location.compare(p2.work_location) == 0)
        return 3.0;
    else
        return 0.25 * 3.0;
}

/* If the two persons have the same current location, then compute_current_location
    would return a weight of 3.5 else return 25% of total weight (assumption that they can still be friends 40% of the time*/
float compute_current_location(person p1,person p2)
{
    if(p1.current_location.compare(p2.current_location) == 0)
        return 3.5;
    else
        return 0.25 * 3.5;
}

/* If the two persons have the same place of birth location, then compute_place_of_birth
    would return a weight of 2.5 else return 25% of total weight (assumption that they can still be friends 40% of the time*/
float compute_place_of_birth(person p1,person p2)
{
    if(p1.place_of_birth.compare(p2.place_of_birth) == 0)
        return 2.5;
    else
        return 0.25 * 2.5;
}

/* If the two people are away in graph by more than two people, then there is lesser chance ofbecoming friends. 
    So assign 2.0 if they are lesser than 2 persons away else assign 25% of 2.0 */
float compute_distance_similarity(int shortest_distance)
{
    if(shortest_distance <= 2)
        return 2.0;
    else
        return 0.25 * 2.0;
}

/* If the two persons are within an age range of less than5 years, this function would return a weight of 1.0
    else if it is in the range 5 to 10 years, return a weight of 0.5 else return a weight of 0.25 */
float compute_age_range(person p1,person p2)
{

    char buf1[10], buf2[10];
    int p = 0, p1_year, p2_year;
    float age_pt;

    //Get the year of birth from date of birth for person1
    for(int it=6; it<p1.dob.length(); ++it)
        buf1[p++] = p1.dob.at(it);
    buf1[4] = '\0';

    //Convert it into integer
    p1_year = atoi(buf1);

    p = 0;

    //Get the year of birth from date of birth for person2
    for(int it=6; it<p2.dob.length(); ++it)
        buf2[p++] = p2.dob.at(it);
    buf2[4] = '\0';

    //Convert it into integer
    p2_year = atoi(buf2);

    //Assign weights as mentioned above in the overview of the function
    if (abs(p2_year - p1_year) < 5)
        age_pt = 1.0;
    else if (abs(p2_year - p1_year) >= 5 && abs(p2_year - p1_year) < 10)
        age_pt = 0.5;
    else
        age_pt = 0.25;
    return age_pt;
}



/* Computes similarity measure between two persons who are directly connected 
    No mutual friends factor since they are already friends */

float compute_intermediate_similarity(person p1,person p2,int shortest_distance)
{

    //Computes age weight
    float age_range = compute_age_range(p1,p2);
    
    //Computes place of birth weight
    float place_of_birth_value = compute_place_of_birth(p1,p2);
   
    //Computes current location weight
    float current_location_value = compute_current_location(p1,p2);
    
    //Computes work location weight
    float work_location_value = compute_work_location(p1,p2);
   
    //Computes high school weight
    float high_school_value = compute_high_school(p1,p2);

    //Compute distance similarity
    float distance_value = compute_distance_similarity(shortest_distance);

    //  Similarity Measure  =  (Sum of weights contributed by all attributes/Maximum possible weight)
    float intermediate_similarity_measure = (age_range + place_of_birth_value + current_location_value + work_location_value + high_school_value + distance_value)/17.0;

    //Return the similarity measure
    return intermediate_similarity_measure;
}

/* Calculates total average similarity between P1 and P2 and returns
    1 if total average similarity is greater than 0.5 else return 0 */
int compare_total_similarity(person p1,person p2,int p1_id,int p2_id,float impact_factor1,float impact_factor2, int shortest_distance)
{

    int mutual_friends_count;
    
    //Computes age weight
    float age_range = compute_age_range(p1,p2);
    cout <<"\nAge range similarity value:"<<age_range;

    //Computes place of birth weight
    float place_of_birth_value = compute_place_of_birth(p1,p2);
    cout<< "\nPlace of birth similarity value :"<<place_of_birth_value;

    //Computes current location weight
    float current_location_value = compute_current_location(p1,p2);
    cout<< "\nCurrent location similarity value :"<<current_location_value;

    //Computes work location weight
    float work_location_value = compute_work_location(p1,p2);
    cout << "\nWork location similarity value :"<<work_location_value;

    //Computes high school weight
    float high_school_value = compute_high_school(p1,p2);
    cout << "\nHigh school similarity value :"<<high_school_value;

    //Compute distance similarity
    float distance_value = compute_distance_similarity(shortest_distance);
    cout << "\nDistance similarity value :"<<distance_value;

    //Computes mutual friends weight and count
    float mutual_friends_score = compute_mutual_friends(p1,p2);
    cout << "\nMutual friends similarity score " << mutual_friends_score;

    //Similarity measure between P1 and P2
    float final_similarity_measure_no_impact = (age_range + place_of_birth_value + current_location_value + work_location_value + high_school_value+mutual_friends_score + distance_value)/23.0;
    
    //Similarity measure between P1 and Px
    float final_similarity_measure_impact1 = (impact_factor1 +age_range + place_of_birth_value + current_location_value + work_location_value + high_school_value+mutual_friends_score + distance_value)/24.0;
    
    //Similarity measure between Px and P2
    float final_similarity_measure_impact2 = (impact_factor2 + age_range + place_of_birth_value + current_location_value + work_location_value + high_school_value+mutual_friends_score + distance_value)/24.0;

    //Combined Average Similarity measure between P1 and P2
    float combined_average_similarity_measure = (final_similarity_measure_impact1 + final_similarity_measure_impact2 + final_similarity_measure_no_impact)/3.0;
    cout << "\n\nFriendship Likelihood Measure : "<<combined_average_similarity_measure<<"\n";
    
    /* If the COmbined Average Similarity measure is greater than 0.5, return 1 (meaning they can possibly be friends)
        else return 0 (meaning they possibly cannot be friends) */
    if(combined_average_similarity_measure>=0.5)
        return 1;
    else
        return 0;
}
int main()
{

    // Utility variables declared for various purposes
    int val,n,p1,p2,n2,shortest_distance,flag=0;      
    string str;

    // File object
    ifstream infile;                

    // Testcase file name (Set of testcases available in Test folder) 
    infile.open ("testcase2.txt");  

    // Extracts the number of people in the given network
    getline(infile,str);
    n = stoi(str);                  

    // Creates a graph with n vertices
    Graph g(n);          

    //Create an adjacency matrix
    int adjacency_matrix[n][n];        

    // Initialize the adjacency matrix to 0
    for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                adjacency_matrix[i][j] = 0;       

    /* Array id makes a one-to-one mapping of vertex number in graph to array index
    Vertex 0 is mapped to id[0], vertex 1 to id[1] and so on */
    int id[n];                      

    // Create an array of n objects for Person class
    person p[n];                                    

    // Read the input from file and populate all the attributes for all n persons in the network
    for(int i=0;i<n;i++)            
    {
        id[i]=i;
        if(!infile.eof())
        {
            getline(infile,str);
            p[i].name.assign(str);
            getline(infile,str);
            p[i].dob.assign(str);
            getline(infile,str);
            p[i].place_of_birth.assign(str);
            getline(infile,str);
            p[i].work_location.assign(str);
            getline(infile,str);
            p[i].current_location.assign(str);
            getline(infile,str);
            p[i].high_school.assign(str);
            getline(infile,str);

            // Get the number of friends for each person and append it to friends list
            n2 = stoi(str);
            for(int j=0;j<n2;j++)                   
            {
                getline(infile,str);
                val = stoi(str);

                // Add an edge between two vertices (persons) in graph if they're friends
                p[i].friends_list.push_back(val);   
                g.addlink(i,val);       

                // Populate the adjacency matrix
                adjacency_matrix[i][val] = 1;            
            }
        }
    }
    infile.close();

    // Get the ids of two persons for whom we wish to determine if they are friends or not (Say P1 and P2)
    cout << "\nEnter the two persons numbers between 0 and "<<n-1<<" to estimate the likelihood of friendship\n";  
    cin>>p1>>p2;

    // If invalid ids are given, display error message and return
    if(p1 < 0 || p1 >= n || p2 < 0 || p2 >= n)          
    {
        cout << "\nError : Either one or both persons are not in the graph network\n";
        return 0;
    }

    // If the two persons are same, return
    if(p1 == p2)
    {
        cout << "\nThe two persons "<<p1<<" "<<p2<<" are same\n";
        return 0;
    }

    // If the two given persons are already friends, print the message and return
    list <int> :: iterator it;
    for(it=p[p1].friends_list.begin();it!=p[p1].friends_list.end();it++)        
        if(p2 == *it)
        {
            cout << "\n" << p1 <<" and " << p2 <<" are already friends\n";
            flag = 1;
            return 0;
        }

    if(flag!=1)
    {

        // Do Dijkstra's algorithm to find the distance between the two persons P1 and P2 in the graph 

        int src=p1, dst=p2;

        // Stores the shortest distance between P1 and all persons in graph
        int dist[n];    

        bool sptSet[n];

        for(int i=0;i<n;i++)
        {
            // Set initial distance to Integer max =(32767)
            dist[i] = MAX;
            sptSet[i] = false;
        }

        // Distance of source is set to 0
        dist[src] = 0;

        for(int c=0;c<n-1;c++)
        {
            int u = minDistance(dist,sptSet,n);
            sptSet[u] = true;

            for(int v=0;v<n;v++)
            {
                /*Update dist[v] only if is not in sptSet, there is an edge from 
                    u to v, and total weight of path from src to  v through u is 
                    smaller than current value of dist[v] */
                if(!sptSet[v] && adjacency_matrix[u][v] && dist[u] != MAX && dist[u]+adjacency_matrix[u][v] < dist[v])
                        dist[v] = dist[u] + adjacency_matrix[u][v];
            }
        }
        for (int i = 0; i < n; i++)
        {
            if(i==dst)
            {
                shortest_distance = dist[i];
                break;
            }
        }

         /* Do Breadth-First-Search from P1 until P2 is found. Return the parent of P2 (say Px). 
            Px is the intermediate node.*/ 
        int intermediate_node = g.BFS(id[p1],id[p2]);                      

        // Compute the similarity between P1 and Px. That gives imapct_factor1
        float impact_factor1 = compute_intermediate_similarity(p[p1],p[intermediate_node],shortest_distance); 

        // Compute the similarity between Px and P2. That gives imapct_factor2
        float impact_factor2 = compute_intermediate_similarity(p[intermediate_node],p[p2],shortest_distance); 

        // Print details of the two persons
        cout<<"\n";
        cout<<"Person ID : "<<id[p1]<<"\n";
        p[p1].print();
        cout<<"\n";
        cout<<"Person ID : "<<id[p2]<<"\n";
        p[p2].print();
 
        // Using these impact factors, calculate the similarity between P1 and P2
        if(compare_total_similarity(p[p1],p[p2],id[p1],id[p2],impact_factor1,impact_factor2,shortest_distance) == 1)  
            cout << "\nPersons " << p1 <<" and " << p2 <<" can possibly be friends\n\n";            
        else
            cout << "\nPersons " << p1 <<" and " << p2 <<" cannot possibly be friends\n\n";
        return 0;
    }
}
