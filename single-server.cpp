#include<bits/stdc++.h>
using namespace std;
vector<float> inter_arrival, service;
vector<float> arrival, departure;
vector<pair<float, char>> all_time;
vector<int> customers_in_system;
vector<int> customers_in_queue;

void get_interarrival_times(int n)
{
    cout << "Enter Inter Arrival times of all customers in order: ";
    for (int i = 0; i < n;i++)
    {
        float time;
        cin >> time;
        inter_arrival.push_back(time);
    }
}

void get_service_times(int n)
{
    cout << "Enter Service times of all customers in order: ";
    for (int i = 0; i < n;i++)
    {
        float time;
        cin >> time;
        service.push_back(time);
    }
}

void calculate_arrival_times(int n)
{
    float time = inter_arrival[1];
    arrival.push_back(time);
    for (int i = 2; i <= n;i++)
    {
        time += inter_arrival[i];
        arrival.push_back(time);
    }
}

void print_arrival_times(int n)
{
    cout << "\nArrival Times are: ";
    for (int i = 1; i <= n;i++)
    {
        cout << arrival[i] << " ";
    }
}

void calculate_departure_times(int n)
{
    float time = arrival[1] + service[1];
    departure.push_back(time);
    for (int i = 2; i <= n;i++)
    {
        float departure_time = max(arrival[i], departure[i - 1]) + service[i];
        departure.push_back(departure_time);
    }
}

void print_departure_times(int n)
{
    cout << "\nDeparture Times are: ";
    for (int i = 1; i <= n;i++)
    {
        cout << departure[i] << " ";
    }
}

void get_all_times(int n)
{
    for (int i = 1; i <= n;i++)
    {
        pair<float, char> arr(arrival[i], 'A');
        all_time.push_back(arr);

        pair<float, char> dep(departure[i], 'D');
        all_time.push_back(dep);

        sort(all_time.begin(), all_time.end());
    }
}

void num_of_customers()
{
    int count = 0;
    for (int i = 0; i < all_time.size();i++)
    {
        if(all_time[i].second == 'A')
        {
            count++;
        }
        else if(all_time[i].second == 'D')
        {
            count--;
        }
        customers_in_system.push_back(count);

        if(count <= 1)
        {
            customers_in_queue.push_back(0);
        }
        else
        {
            customers_in_queue.push_back(count - 1);
        }
    }
}

void print_system_customers()
{
    cout << "\n\nNumber of Customers in System at a particular time:";
    cout << "\nTime\t\tCustomers";
    for (int i = 0; i < all_time.size(); i++)
    {
        cout <<"\n"<<all_time[i].first << "\t\t" << customers_in_system[i];
    }
}

void print_queue_customers()
{
    cout << "\n\nNumber of Customers in Queue at a particular time:";
    cout << "\nTime\t\tCustomers";
    for (int i = 0; i < all_time.size(); i++)
    {
        cout <<"\n"<<all_time[i].first << "\t\t" << customers_in_queue[i];
    }
}

void avg_system_customers()
{
    float total = 0, time = 0;
    int siz = all_time.size();
    for (int i = 1; i < siz;i++)
    {
        total += (all_time[i].first - all_time[i - 1].first) * customers_in_system[i - 1];
    }
    cout << "\n\nAverage number of customers in system is " << total / all_time[siz - 1].first<<endl;
}

void avg_queue_customers()
{
    float total = 0, time = 0;
    int siz = all_time.size();
    for (int i = 1; i < siz;i++)
    {
        total += (all_time[i].first - all_time[i - 1].first) * customers_in_queue[i - 1];
    }
    cout << "\nAverage number of customers in queue is " << total / all_time[siz - 1].first<<"\n\n";
}

int main()
{
    int n;
    cout << "Enter number of customers: ";
    cin >> n;
    inter_arrival.push_back(0);
    service.push_back(0);
    arrival.push_back(0);
    departure.push_back(0);

    // Input Inter Arrival Times
    get_interarrival_times(n);

    // Input Service times
    get_service_times(n);

    // Arrival Times
    calculate_arrival_times(n);

    // Departure Times
    calculate_departure_times(n);

    // Print Arrival Times
    print_arrival_times(n);

    // Print Departure Times
    print_departure_times(n);

    get_all_times(n);

    num_of_customers();

    print_system_customers();

    print_queue_customers();

    avg_system_customers();

    avg_queue_customers();
}

// Input

// Arrival Times
// 0.4 1.2 0.5 1.7 0.2 1.6

// Service Times
// 2.0 0.7 0.2 1.1 3.7 0.6
