//@Mustafa Adam
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define n 32
int main(){
    //I am using array data strcture to solve this project
    int numberOfnode=n*0.3; //the pecentage of the actual nodes that will be online
    int node[numberOfnode];  //number of online nodes
    int i;
    int s;
    int finger[numberOfnode][5]; //this hold the finger table for the nodes
    //here generating the random nodes
    srand(time(NULL));   
    for(i=0;i<numberOfnode;i++){
        node[i]=rand() % n+1;
    }
    //this section here will make sure that there is no any repeated node of the random generated nodes if there is any it will come back to rt: to generate new random one
    rt:
    for(i=0;i<numberOfnode;i++){
        for(s=0;s<numberOfnode;s++){
            if(s==i)
                continue;
            if(node[i]==node[s])
                node[i]=rand() % n+1;
        }

    }
    
    for(i=0;i<numberOfnode;i++){
        for(s=0;s<numberOfnode;s++){
            if(s==i)
                continue;
            if(node[i]==node[s])
                goto rt;
        }

    }


    //after making all the nodes random and no repeated node will try to sort the nodes using buble sort of Big O(n); to give me better view of the circuler nodes
    int x;
    for(i=numberOfnode;i>0;i--){
        for(x=0;x<i-1;x++){
            if(node[x]>node[x+1]){
                int temp=node[x];
                node[x]=node[x+1];
                node[x+1]=temp;
            }
                
        }
    }

    //in this section try to generate the keys that every node reponsible for
    int keys[numberOfnode][n];
    int d;
    for(i=numberOfnode-1;i>=0;i--){
        //this special case when you get to the last node and trying to get the other side of the keys
        if(i==0){
            int d=node[i];
            int f;
            for(f=0;d>=0;f++,d--){
                keys[i][f]=d;
            }
            for(d=node[numberOfnode-1]+1;d<=n;d++,f++){
                keys[i][f]=d;
            }
            keys[i][f]=-1; //at the end add this -1 to indecate the end of the keys of that node
            continue;
        }

        for(d=0,x=node[i];x>node[i-1];x--,d++){
            keys[i][d]=x;
        }
        keys[i][d]=-1;//at the end add this -1 to indecate the end of the keys of that node
    }
    //in this coming section will try to generate the finger table
    int suc=0;
    int f;
    int q;
    for(i=0;i<numberOfnode;i++){
        for(x=1;x<6;x++){
            suc=node[i]+(pow(2,(x-1)));
            if(suc>n)
                suc-=n;
            for(f=0;f<numberOfnode;f++){
                for(q=0;keys[f][q]!=-1;q++){
                    if(suc==keys[f][q]){
                        finger[i][x-1]=node[f];
                        f=numberOfnode;
                        break;
                    }//end of if                        
                }//end of inner loop
            }//end of outer loop
        }//end of outer outer loop

    }//end of outer outer outer loop
    //in this seciton will try to print out the output
    int z;
    for(i=0;i<numberOfnode;i++){
        printf("\nNode %d :  {",node[i]);
        for(x=0;keys[i][x]!=-1;x++)
            printf(" %d ",keys[i][x]);
        printf("}\nFinger table:\n");
            for(z=0;z<5;z++)
                printf("%d	  %d\n",(z+1),finger[i][z]);
    }
    //this section for looking up key in the DHT
    srand(time(NULL)); 
    //int ranKey;
    int rannode;  
    for(i=0;i<5;i++){
        int rankey=rand() % n+1;
        int randindex=rand() % numberOfnode;
        rannode=node[randindex];
        int nextrandnode=0;
        
        printf("Look up k = %d from node %d: ",rankey,rannode);
        for(x=0;x<numberOfnode;x++){
                int k=0;
                printf("%d>",node[randindex]);
            //here to check for the last node by looking into the keys table
            for(q=0;keys[randindex][q]!=-1;q++){
                if(rankey==keys[randindex][q]){
                    x=numberOfnode;
                    k=1;
                    break;
                }   
            }
            if(node[randindex] < rankey &&rankey < finger[randindex][0]){
                k=1;
                nextrandnode=finger[randindex][q];
                //printf("entered here");
            }
            //if the it's not the last node from the previous loop then will try to find our next move "the index of our next move" by looking noto the finger table
            if(k==0){//if1
                for(q=0;q<5;q++){
                    //printf("    <%d %d>     ",rankey,finger[randindex][q]);
                    if(finger[randindex][q]<=rankey&&rankey<finger[randindex][q+1]){
                        nextrandnode=finger[randindex][q];
                        break;
                    }
                    else if(finger[randindex][q]==rankey){
                        nextrandnode=finger[randindex][q];
                        break;
                    }
                    if(finger[randindex][q]>rankey&&finger[randindex][q+1]>rankey&&finger[randindex][q]>finger[randindex][q+1]){
                        nextrandnode=finger[randindex][q];
                        break;
                    }
                    if(finger[randindex][q]<rankey&&finger[randindex][q+1]<rankey&&finger[randindex][q]>finger[randindex][q+1]){
                        nextrandnode=finger[randindex][q];
                        break;
                    }
                    else
                        nextrandnode=finger[randindex][q];
                }
                //this section to find the index of the next node
                for(q=0;q<numberOfnode;q++)
                    if(node[q]==nextrandnode)
                        randindex=q;
            }//end of if 1
        }//end of for
        printf("\n");
    }//end of for loop


return 0;
}

