#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
int k=1,num=1,source,destination,route_num,seat_num,age,temp,tic_num=15324;
#define max_vertices 7

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjacencyList;
} Graph;
Graph*graph;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->adjacencyList = (Node**)malloc(numVertices * sizeof(Node));

    for (int i = 0; i < numVertices; ++i) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}
typedef struct {
    int data[max_vertices];
    int top;
} Stack;

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}


void push(Stack* stack, int item) {
    stack->data[++stack->top] = item;
}

int pop(Stack* stack) {
    return stack->data[stack->top--];
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

typedef struct {
    int data[max_vertices];
    int front;
    int rear;
} Queue;

void enqueue(Queue* queue, int item) {
    queue->data[++queue->rear] = item;
}

int dequeue(Queue* queue) {
    return queue->data[++queue->front];
}

bool isQueueEmpty(Queue* queue) {
    return queue->front == queue->rear;
}

bool isVisited[max_vertices];

void initializeVisited() {
    for (int i = 0; i <max_vertices; i++) { // enduku ante previous traversal chesinapudu adhi visited ah kadha ani check cheyaniki
        isVisited[i] = false;
    }
}

void BFS(Graph* graph, int source, int destination){
    Queue queue;
    queue.front = -1;
    queue.rear = -1;

    int parent[max_vertices]; // declaring the parent array 
    for (int i = 0; i <max_vertices; i++) {
        parent[i] = -1;        // initalize the parent array to -1 
    }

    enqueue(&queue, source); // source vetex ni queue lopali pompistam 
    isVisited[source] = true;    // we will mark that source as visited 

    while (!isQueueEmpty(&queue)) { // unitl the queue is empty 
        int currentVertex = dequeue(&queue);

        if (currentVertex == destination) {
            printf("route %d: ",k);
            int v = destination;
            while (v != -1) {
                printf("%d ", v);
                v = parent[v];
            }
            printf("\n");
            k++;
            return;
        }
        Node* temp = graph->adjacencyList[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!isVisited[adjVertex]) {
                enqueue(&queue, adjVertex);
                isVisited[adjVertex] = true;
                parent[adjVertex] = currentVertex;
            }
            temp = temp->next;
        }
    }
    
}

void DFSUtil(Graph* graph, int currentVertex, int destination, bool* isVisited, int* parent) {
    if (currentVertex == destination) {
        printf("route %d: ",k);
        int v = destination;
        while (v != -1) {
            printf("%d ", v);
            v = parent[v];
        }
        printf("\n");
        k++;
        return;
    }

    isVisited[currentVertex] = true;

    Node* temp = graph->adjacencyList[currentVertex];
    while (temp) {
        int adjVertex = temp->data;
        if (!isVisited[adjVertex]) {
            parent[adjVertex] = currentVertex;
            DFSUtil(graph, adjVertex, destination, isVisited, parent);
        }
        temp = temp->next;
    }
}

void DFS(Graph* graph, int source, int destination) {
    bool isVisited[max_vertices];
    int parent[max_vertices];
    for (int i = 0; i <max_vertices; i++) {
        isVisited[i] = false;
        parent[i] = -1;
    }

    DFSUtil(graph, source, destination, isVisited, parent);

}
void design(){
    int n=50;
    while(n--)
    printf("-");
    printf("\n");
}


void loading(){
    printf("PLEASE WAIT..");
    for(int i=1;i<3;i++){
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    printf("\n");
}

struct person_details{
    char name[30];
    int age;
    char mobile_num[10];
};

struct bus_details{
    int bus_number;
    int bus_seats[10];
    int is_exchange[10];
   struct person_details person_det[10];
};
struct bus_details bus[25];
void get_point(int n){
    switch(n){
        case 0:
        printf("CHENNAI");
        break;
         case 1:
        printf("BENGALURU");
        break;
         case 2:
        printf("MUMBAI");
        break;
         case 3:
        printf("DELHI");
        break;
         case 4:
        printf("KOLKATA");
        break;
         case 5:
        printf("PUNJAB");
        break;
         case 6:
        printf("GUJARAT");
        break;
    }
}
void generate_bill(int busnum,int seat_num,int n){
    int temp1=busnum%10;
    int temp=busnum/10;
    int temp2=temp%10;
    
    loading();
    time_t current_time;
    char* time_string;
    current_time=time(NULL);
    time_string=ctime(&current_time);
    design();
    printf("\t\tAPSRTC BUS TICKET");
    printf("\n%s\n",time_string);
    printf("ticket number: %d\n",tic_num);
    design();
        printf("YOUR BUS NUMBER: %d\n",busnum);    
        printf("YOUR SEAT NUMBER:%d\n", seat_num);
        printf("SOURCE: ");
        get_point(temp1);
        printf("\nDESTINATION: ");
        get_point(temp2);
        for(int i=1;i<=25;i++){
            if(bus[i].bus_number==busnum){
        printf("\nNAME OF THE PASSENGER:%s\n",bus[i].person_det[seat_num].name);
        printf("PASSENGER AGE:%d\n",bus[i].person_det[seat_num].age);
        printf("PASSENGER MOBILE NUMBER:%s\n",bus[i].person_det[seat_num].mobile_num);
            }
        }
        printf("TOTAL AMOUNT : %d\n",n*100);
        design();
        printf("THANK YOU.PLEASE VISIT US AGAIN..\n");
        design();
    tic_num++;
    
}
void book_tickets(){
    int m=0,n,pay;
     printf("CHOOCE YOUR ROUTE NUMBER\n");
     scanf("%d",&route_num);
     int busnum=(route_num*100)+(destination*10)+source;
 loading();
   printf("BUS NUMBER IS: ");  
   printf("%d\n",busnum);
   
   if(num==1){
    bus[num].bus_number=busnum;
   }
   else{
    for(int i=1;i<=num;i++){
        if(bus[i].bus_number==busnum){
           m++;
        }
    }
    if(m==0)
        bus[++num].bus_number=busnum;
   }
  
  printf("\t\tAVAILABLE SEATS\n");
   for(int j=1;j<=25;j++){
      if(bus[j].bus_number==busnum){
        for(int s=1;s<=10;s++){
        if(bus[j].bus_seats[s]!=1)
        printf("%d =AVAILABLE\n",s);
        else{
            printf("%d =RESERVED\n",s);
        }
       }
       break;
    }

 }
 printf("ENTER NUMBER OF TICKETS:");
 scanf("%d",&n);

for(int i=1;i<=n;i++){
    printf("CHOOCE YOUR SEAT NUMBERS\n");
    scanf("%d",&seat_num);
   for(int j=1;j<=25;j++){
    if(bus[j].bus_number==busnum ){
        if(bus[j].bus_seats[seat_num]==0){
                  bus[j].bus_seats[seat_num]=1;
        }
    else{
        printf("SEAT IS ALREADY RESERVED.PLEASE SELECT YOUR SEAT AGAIN\n");
        printf("CHOOCE YOUR SEAT NUMBERS\n");
       scanf("%d",&seat_num);
       for(int j=1;j<=25;j++){
        if(bus[j].bus_number==busnum ){
           if(bus[j].bus_seats[seat_num]==0)
                  bus[j].bus_seats[seat_num]=1;
      }
    }
  }
}
}
   printf("ENTER YOUR NAME of person : ");
   scanf("%s",bus[num].person_det[seat_num].name);
   printf("ENTER YOUR AGE person : ");
   scanf("%d",&bus[num].person_det[seat_num].age);
   printf("ENTER YOUR MOBILE NUMBER person : ");
   scanf("%s",bus[num].person_det[seat_num].mobile_num);
   
    }
    printf("DO YOU WANT TO GO FOR PAYMENT(0/1):");
    scanf("%d",&pay);
    if(pay==1)
    generate_bill(busnum,seat_num,n);
    else{
        for(int i=1;i<=25;i++){
        if(bus[i].bus_number==busnum)
            bus[i].bus_seats[seat_num]=0; 
            printf("YOUR TICKECT IS NOT BOOKED");  
    }
 }
}
void check_ticket_details(){
   int busno,seatno,a=0;
    printf("ENTER YOUR BUS NUMBER: ");
    scanf("%d",&busno);
    printf("ENTER YOUR SEAT NUMBER: ");
    scanf("%d",&seatno);
    design();
    printf("\t**TICKET DETAILS**\n");
   for(int i=1;i<25;i++){
    if(bus[i].bus_number==busno){
        if(bus[i].bus_seats[seatno]==1){
        printf("YOUR BUS NUMBER: %d\n",bus[i].bus_number);    
        printf("YOUR SEAT NUMBER:%d\n", seatno);
        printf("NAME OF THE PASSENGER:%s\n",bus[i].person_det[i].name);
        printf("PASSENGER AGE:%d\n",bus[i].person_det[i].age);
        printf("PASSENGER MOBILE NUMBER:%s\n",bus[i].person_det[i].mobile_num);
        }
        else{
            printf("NO RESULT FOUND\n");
        }
        
        a++;
       break;
    }
    if(a==0)
    printf("ENTER VALID DETAILS");
    
   }
}
void cancel_tickets(){
    int busno,seatno,i,a=0;
    printf("ENTER YOUR BUS NUMBER: ");
    scanf("%d",&busno);
    printf("ENTER YOUR SEAT NUMBER: ");
    scanf("%d",&seatno);
    for(i=1;i<=25;i++){
        if(bus[i].bus_number==busno){
            if(bus[i].bus_seats[seatno]==1){
            bus[i].bus_seats[seatno]=0;
            a++;
            }
            else
            printf("PLEASE CHECK YOUR SEAT NUMBER.");
            
        }
    }
    if(a==0)
    printf("SEAT HASN'T BEEN BOOKED\n");

}
void check_tickets_available(){
    int k=0;
printf("ENTER YOUR ROUTE NUMBER: ");
scanf("%d",&route_num);
int busnum=(route_num*100)+(destination*10)+source;
 printf("\t\tAVAILABLE SEATS\n");
   for(int j=1;j<=num;j++){
      if(bus[j].bus_number==busnum){
        k++;
        for(int s=1;s<=10;s++){
        if(bus[j].bus_seats[s]!=1)
        printf("%d =AVAILABLE\n",s);
        else{
            printf("%d =NOT AVAILABLE\n",s);
        }
       }
       break;
    }
 }
 if(k==0){
    
        bus[num++].bus_number=busnum;
        for(int i=1;i<=10;i++){
            printf("%d =AVAILABLE\n",i);
        }
    
 }

}
void exchange_seats_available(int busno){
    for(int i=1;i<=25;i++){
        if(bus[i].bus_number==busno){
            for(int j=1;j<=10;j++){

                if(bus[i].bus_seats[j]==0)
                printf("%d =AVAILABLE\n",j);
                else
                printf("%d =NOT AVAILABLE\n",j);
            }
        }
    }
}
void seat_transfer(){
    int busno,seatno,newseat_no;
    printf("ENTER YOUR BUS NUMBER:");
    scanf("%d",&busno);
    printf("ENETR YOUR OLD SEAT NUMBER:");
    scanf("%d",&seatno);
    exchange_seats_available(busno);
    printf("ENTER YOUR NEW SEAT NUMBER:");
    scanf("%d",&newseat_no);
    for(int i=1;i<=25;i++){
        if(bus[i].bus_number==busno){
            bus[i].bus_seats[seatno]=0;
            bus[i].bus_seats[newseat_no]=1;
            bus[i].person_det[newseat_no].age= bus[i].person_det[seatno].age;
            strcpy(bus[i].person_det[newseat_no].mobile_num,bus[i].person_det[seatno].mobile_num);
             strcpy(bus[i].person_det[newseat_no].name,bus[i].person_det[seatno].name);
        } 
    }
    printf("YOUR SEAT HAS BEEN TRANSFERED\n");
    design();
}
void exchange_tickets(){
    int busno,seatno;
   printf("ENTER YOUR BUS NUMBER:");
   scanf("%d",&busno);
   printf("ENTER YOUR SEAT NUMBER:");
   scanf("%d",&seatno);

   for(int i=1;i<=25;i++){
    if(bus[i].bus_number==busno){
       bus[i].is_exchange[seatno]=1;
    }
   }
}
void check_exchange_details(){
    int temp_busno,routeno;
    printf("ENTER THE PICKUP POINT: ");
    scanf("%d", &source);
    printf("ENTER YOUR DESTINATION POINT: ");
    scanf("%d", &destination);
    temp_busno=destination*10+source;
     
    for(int i=0;i<=25;i++){
    if(bus[i].bus_number%100==temp_busno){
        printf("YOU HAVE BUS NUMBER:%s\n",bus[i].bus_number);
        for(int j=1;j<=10;j++){
            printf("SEATS FOR EXCHANGING:\n");
       if(bus[i].is_exchange[j]==1)
       printf("%d =EXCHANGABLE\n",j);
        }
        break;    
    }
   }  
}
void menu(){
        printf("\tBUS TICKET RESERVATION\n");
        design();
        printf("1.BOOK TICKETS\n2.CANCEL TICKET \n3.CHECK TICKET AVAILABLE\n");
        printf("4.CHECK TICKETS DETAILS\n5.EXCHANGE TICKET\n6.SEAT TRANSFER\n7.CHECK EXCHANGABLE SEATS\n8.EXIT\n");
}
void busstop_details(){
     design();
     printf("\t\t BUS STOP CODES\n");
     printf("CHENNAI - 0\nBENGALURU - 1\nMUMBAI - 2\nDELHI - 3\nKOLKATA - 4\nPUNJAB - 5\nGUJARAT - 6\n");
     design();
}

int main() {
    int choice,route=0;
    int numVertices = 7;
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 6);
    addEdge(graph, 5, 6);
    while(1){
        
        design(); // ---------------- lines kosam 
        menu(); //  defining user asking order 
        design(); 
            printf("ENTER YOUR CHOICE: ");
            scanf("%d",&choice);
                switch(choice){
             case 1: // to book tickets 
             busstop_details(); // defining bus stops like cheenai and etc.  //  495
             printf("ENTER THE PICKUP POINT: ");
             scanf("%d", &source);
             printf("ENTER YOUR DESTINATION POINT: ");
             scanf("%d", &destination);
                
            printf("BUSSES AVAILABLE TO YOU\n");
          
            initializeVisited();
            BFS(graph, source, destination); // bfs is used 

            initializeVisited();
            DFS(graph, source, destination); // dfs is used 
              book_tickets();
              
              k=1;
              break;
            case 2:
              cancel_tickets(); 
              break;
            case 3:
            busstop_details();
            printf("ENTER THE PICKUP POINT: ");
            scanf("%d", &source);
            printf("ENTER YOUR DESTINATION POINT: ");
            scanf("%d", &destination);
            printf("BUSSES AVAILABLE TO YOU\n");

            initializeVisited();
            BFS(graph, source, destination);

            initializeVisited();
            DFS(graph, source, destination);
              check_tickets_available();
              k=1;
              break;
            case 4:
              check_ticket_details();
              break;
            case 5:
              exchange_tickets();
              break;
            case 6:
              seat_transfer();
              break; 
            case 7:
               check_exchange_details();
               break;
            case 8:
            printf("\t\tTHANK YOU FOR VISITING\n");
            design();
              exit(0);
              break;
            default:
            printf(" PLEASE CHOOSE VALID OPTION\n");
            break;  
      }
    }
    return 0;
}
