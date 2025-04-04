#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) 
{
    // a queue contains data, a linked list
    size_t state_serialized = serialize(state);
    insert_at_tail(&(q -> data), state_serialized);
}

struct game_state dequeue(struct queue *q) 
{ 
    size_t dequeued_value = remove_from_head(&(q -> data));
    return deserialize(dequeued_value);
}

int number_of_moves(struct game_state start) 
{ 
    // serialize goal state
    struct game_state goal = {
        .empty_row = 3,
        .empty_col = 3,
        .num_steps = 0
    };

    for(uint8_t row = 0; row < 4; row++)
    {
        for(uint8_t col = 0; col < 4; col++)
        {
            goal.tiles[row][col] = col + 1 + 4 * row;
        }
    }
    goal.tiles[3][3] = 0;

    size_t goal_serialized = serialize(goal);
    /*
        queue
            linked_list data
                list_node* head
                    list_node* next
                    size_t value - serialized game state 
        */

    // Create a queue with a single head node matching game_start
    
    struct queue queue = {.data = {.head = NULL}};
    enqueue(&queue, start);
    
    // consume next node in queue by dequeuing and checking dequeued value. 
    // If the value does not match goal, queue up its next possible moves, including backtracks???
    //repeat
    struct game_state curr_state;
    //struct game_state right_state, down_state, left_state, up_state;
    enum Direction {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };

    struct game_state children[4];
    size_t children_serialized[4];
    struct list_node* curr;
    int numtries = 0;
    int duplicate = 0;
    while(queue.data.head != NULL)
    {
        fprintf(stdout, "\n\ntries: %d\n\nduplicates: %d\n\n", numtries, duplicate);
        numtries++;
        curr_state = dequeue(&queue);
        goal.num_steps = curr_state.num_steps;
        goal_serialized = serialize(goal);
        //right_state = down_state = left_state = up_state = curr_state;
        

        size_t curr_state_serialized = serialize(curr_state);
            
        if(curr_state_serialized == goal_serialized)
        {
                free_list(queue.data);
                return curr_state.num_steps;
        }
        else
        {
            for(int i = 0; i < 4; i++)
            {
                children[i] = curr_state;
            }
            move_down(&children[DOWN]);
            move_up(&children[UP]);
            move_left(&children[LEFT]);
            move_right(&children[RIGHT]);
            
            for(int i = 0; i < 4; i++)
            {
                children_serialized[i] = serialize(children[i]);
            }
        
        
            for(int i = 0; i < 4; i++)
            {
                curr = queue.data.head;
                int add = 1;
                while(curr != NULL && curr -> next != NULL)
                {
                    if(curr -> value == children_serialized[i])
                    {
                        add = 0;
                        duplicate++;
                        break;
                    }
                    curr = curr -> next;
                }
                if(add)
                {
                    if(children_serialized[i] != curr_state_serialized)
                    {
                        enqueue(&queue, children[i]);
                    }
            
                }
            }
        
        /*
        move_down(&down_state);
        move_up(&up_state);
        move_left(&left_state);
        move_right(&right_state);
        curr = list.head;
        while(curr != NULL && curr -> next != NULL)
    {
        
        curr = curr -> next;
    }
        if(serialize(down_state) != curr_state_serialized)
        {
            enqueue(&queue, down_state);
        }
        if(serialize(up_state) != curr_state_serialized)
        {
            enqueue(&queue, up_state);
        }
        if(serialize(left_state) != curr_state_serialized)
        {
            enqueue(&queue, left_state);
        }
        if(serialize(right_state) != curr_state_serialized)
        {
            enqueue(&queue, right_state);
        }
        */
    }
        
    }

    return -1;
}
