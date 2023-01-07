#include<stdio.h>
#include<stdlib.h>

struct process{
    /*size = size of process
    frag = fragmentation of process
    f_count = amount of frames for each process
    flag = to indicate processes that cannot be allocated
    fr = array of frame nos*/
    
    int size, frag, pid, f_count, flag;
    int fr[20];
}p[10], temp;


int m_size, f_size, f_count, frames[100] = {0}, i, j, count=0, reqd_frames, totalfrag=0;

/*m_size = memory size
f_size = size of each frame
f_count = amount of frames available
frames = array of available frames
count = no of processes available
reqd_frames = frames reqd for each process
totalfrag = total fragmentation*/

void insert();
void delete();

void main(){
    int op;

    for(i=0; i<30; i++){
        frames[i] = 0;
    }

    printf("\nEnter total memory size: ");
    scanf("%d", &m_size);
    printf("\nEnter the frame size: ");
    scanf("%d", &f_size);

    f_count = m_size / f_size;

    do{
        printf("\n\n1.Insert\n2.Delete\n3.Exit\n\n");
        scanf("%d", &op);

        switch(op){
            case 1: {insert(); break;}
            case 2:{delete(); break;}
            case 3:{break;}
        }

    }while(op!=3);

}

void insert(){

    int i=0, j, frame_no,k;
    int flag=0;

    /*frame_no = to store the allocated frame no using rand()
    flag indicating if there are no empty frames*/


    for(i=0; i<20; i++){ //initializing all members of frames of individual processes
        p[count].fr[i] = 0;
    }

    printf("\nProcess pid? ");
    scanf("%d", &p[count].pid);
    printf("\nSize of process? ");
    scanf("%d", &p[count].size);
    
    reqd_frames = p[count].size / f_size;

    if (p[count].size % f_size == 0){
        reqd_frames = reqd_frames;
    }
    else if (p[count].size < f_size){
        reqd_frames = 1;
    }
    else
        reqd_frames = p[count].size / f_size + 1;
        p[count].frag = reqd_frames * f_size - p[count].size;

    p[count].f_count = reqd_frames;

    for(i=0; i<reqd_frames; i++){
        flag = 0; //to indicate if there are no empty frames left. flag = 0 indicates 0 empty frames
        frame_no = rand();
        frame_no = frame_no % f_count;

        if(frames[frame_no] != 1){ //if not already allocated
            frames[frame_no] = 1;
            p[count].fr[i] = frame_no;
        }
        else{
            for(j=0; j<f_count; j++){ // find a new frame if found frame is already allocated
                frame_no = rand();
                frame_no = frame_no % f_count;

                if(frames[frame_no] != 1){
                    flag = 1;
                    frames[frame_no] = 1;
                    p[count].fr[i] = frame_no;
                    break;
                }  
            }
            if(flag == 0){ //setting flag value to processes that can't be allocated
                p[count].flag = -9;
            }
        }
    }

    printf("\nPid\tSize\tFrames\n"); //printing

    for(i=0; i<=count; i++){
        printf("%d\t%d\t", p[i].pid, p[i].size);
        if(p[i].flag != -9){
            for(j=0; j<p[i].f_count; j++){
                printf("%d ", p[i].fr[j]);
            }
        }
        else{
            for(j=0;j<reqd_frames;j++){ //freeing up the frames that were allocated to flagged processes
                for(k=0;k<f_count;k++){
                    if(p[i].fr[j] == k){
                        frames[k] = 0;
                    }
                }
            }
            printf("Not enough frames!");

            for(j=i;j<=count;j++){ //deleting and replacing members with successive members of array
                p[i].flag = 0;
                p[i].frag = 0;
                p[j] = temp;
                p[j] = p[j+1];
                p[j+1] = temp;

            }
            count--;
        }

        printf("\n");
    }

    totalfrag = 0;

    for(i=0;i<=count;i++){ //calculating total internal fragmentation
        totalfrag += p[i].frag;
    }

    printf("\n\nTotal fragmentation: %d\n", totalfrag);
    count++;
}

void delete(){
    
    int del_pid, i, j, k;

    printf("\nEnter pid of process to be deleted: ");
    scanf("%d", &del_pid);

    for(i=0; i<=count;i++){
        if(del_pid == p[i].pid){
            totalfrag -= p[i].frag; //decreasing total fragmentation
            for(j=0;j<p[i].f_count;j++){
                for(k=0;k<f_count;k++){
                    if(p[i].fr[j] == k){
                        frames[k] = 0; //freeing up allocated frames
                    }
                }
            }
            for(j=i;j<=count;j++){ //deleting and replacing with subsequent members
                p[i].flag = 0;
                p[j] = temp;
                p[j] = p[j+1];
                p[j+1] = temp;

            }
            count--;
            break;

        }
    }

    printf("\nPid\tSize\tFrames\n");

    for(i=0; i<count; i++){
        printf("%d\t%d\t", p[i].pid, p[i].size);
        if(p[i].flag != -9){
            for(j=0; j<p[i].f_count; j++){
                printf("%d ", p[i].fr[j]);
            }
        }
        printf("\n");
    }

    printf("\nTotal fragmentation is: %d\n", totalfrag);
}
