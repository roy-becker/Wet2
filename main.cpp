#include <iostream>
using namespace std;
#include "vector"
#include "HashTable.h"
#include "worldcup23a2.h"
#include "deque"

class id_perm{
public:
    int id;
    permutation_t permutation;

    id_perm(int id, permutation_t perm):
            id(id),
    permutation(perm){}
};

void test1(){
    StatusType statusCheck;
    output_t<int> intResult;


    world_cup_t* obj_new = new world_cup_t();

    int permutations [5][5] =
            {
                    {1,3,4,2,0},
                    {0,1,2,4,3},
                    {2,0,4,3,1},
                    {1,2,0,3,4},
                    {4,3,0,1,2}
            };


    obj_new->add_team(100);
    obj_new->add_team(200);
    obj_new->add_team(300);
    obj_new->add_team(400);
    obj_new->add_team(500);
    obj_new->add_team(600);
    obj_new->add_team(700);
    obj_new->add_team(800);
    obj_new->add_team(900);
    obj_new->add_team(1000);





    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 8; ++j) {
            StatusType S = obj_new->add_player(i*100+j,i*100,permutations[(i+j)%5],i%5 + 8, i+ j%6, 0, true);
            if(S != StatusType::SUCCESS)
                cout<<"problem "<< i*100+j<<endl;
        }
    }
    StatusType s;
    s = obj_new->add_player(108,100,permutations[1],9, 1, 0, true);
    s = obj_new->add_player(109,100,permutations[1],1, 1, 0, true);
    s = obj_new->add_player(208,200,permutations[0], 8, 4, 0, true);
    s = obj_new->add_player(608,600,permutations[4], 19, 2, 0, true);

    int result;
    StatusType status;

    cout<<"player match results:"<<endl;

    cout << obj_new->play_match(100,400).ans()<<endl;
    cout << obj_new->play_match(200,600).ans()<<endl;
    cout << obj_new->play_match(900,300).ans()<<endl;
    obj_new->buy_team(100,300);
    obj_new->buy_team(400,200);
    obj_new->buy_team(600,900);
    obj_new->buy_team(1000,700);
    obj_new->buy_team(800,500);

    cout<<"player gp and spirit after buying teams:"<<endl;

    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 10; ++j) {
            cout<<"player number: "<< i*100+j<<endl;
            cout<< obj_new->get_partial_spirit(i*100+j).ans()<<endl;
            cout<< obj_new->num_played_games_for_player(i*100+j).ans()<<endl;

        }
    }

    cout << obj_new->play_match(1000,400).ans()<<endl;
    cout << obj_new->play_match(100,600).ans()<<endl;
    cout << obj_new->play_match(800,1000).ans()<<endl;
    cout << obj_new->play_match(1000,400).ans()<<endl;

    cout<<"player gp and spirit after games played:"<<endl;

    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 10; ++j) {
            cout<<"player number: "<< i*100+j<<endl;
            cout<< obj_new->get_partial_spirit(i*100+j).ans()<<endl;
            cout<< obj_new->num_played_games_for_player(i*100+j).ans()<<endl;

        }
    }

    obj_new->buy_team(100,400);
    obj_new->buy_team(600,800);

    cout<<"player gp and spirit after buying teams:"<<endl;

    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 10; ++j) {
            cout<<"player number: "<< i*100+j<<endl;
            cout<< obj_new->get_partial_spirit(i*100+j).ans()<<endl;
            cout<< obj_new->num_played_games_for_player(i*100+j).ans()<<endl;

        }
    }

    s = obj_new->add_player(111,100,permutations[2],5, 53, 0, true);
    s = obj_new->add_player(112,100,permutations[4],17, 16, 0, true);
    s = obj_new->add_player(611,600,permutations[0], 23, 1, 0, true);
    s = obj_new->add_player(612,600,permutations[1], 1, 4, 0, true);
    s = obj_new->add_player(711,1000,permutations[0], 85, 6, 0, true);
    s = obj_new->add_player(712,1000,permutations[3], 13, 21, 0, true);

    cout<<"player gp and spirit after 2 buys and inserting new players:"<<endl;

    for(int i = 1; i<=7; i++){
        for (int j = 0; j < 13; ++j) {
            cout<<"player number: "<< i*100+j<<endl;
            cout<< obj_new->get_partial_spirit(i*100+j).ans()<<endl;
            cout<< obj_new->num_played_games_for_player(i*100+j).ans()<<endl;

        }
    }

    obj_new->add_team(555);
    obj_new->buy_team(600,100);
    obj_new->buy_team(555,1000);

    for(int i = 1; i<=7; i++){
        for (int j = 0; j < 13; ++j) {
            cout<<"player number: "<< i*100+j<<endl;
            cout<< obj_new->get_partial_spirit(i*100+j).ans()<<endl;
            cout<< obj_new->num_played_games_for_player(i*100+j).ans()<<endl;

        }
    }
}
void test2(){
    world_cup_t* obj_new = new world_cup_t();

    int permutations [5][5] =
            {
                    {1,3,4,2,0},
                    {0,1,2,4,3},
                    {2,0,4,3,1},
                    {1,2,0,3,4},
                    {4,3,0,1,2}
            };

    std::cout << obj_new->get_ith_pointless_ability(0).ans()<<endl;
    if(obj_new->get_ith_pointless_ability(0).status() == StatusType::FAILURE)
        std::cout << "good"<<endl;


    obj_new->add_team(100);
    std::cout << obj_new->get_ith_pointless_ability(0).ans()<<endl;


    obj_new->add_team(200);
    std::cout << obj_new->get_ith_pointless_ability(0).ans()<<endl;
    std::cout << obj_new->get_ith_pointless_ability(1).ans()<<endl;

    obj_new->add_team(300);
    obj_new->add_team(400);
    obj_new->add_team(500);
    obj_new->add_team(600);
    obj_new->add_team(700);
    obj_new->add_team(800);
    obj_new->add_team(900);
    obj_new->add_team(1000);


    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 8; ++j) {
            StatusType S = obj_new->add_player(i*100+j,i*100,permutations[(i+j)%5],i%5 + 8, (i+ j)%6, 0, true);
            if(S != StatusType::SUCCESS)
                cout<<"problem "<< i*100+j<<endl;
        }
    }

    obj_new->buy_team(300,100);
    obj_new->buy_team(900,700);


    for (int i = 0; i <= 10; ++i) {
        cout<<"index: "<<i<<endl;
        std::cout << obj_new->get_ith_pointless_ability(i).ans()<<endl;

    }

}
void test3(){

    world_cup_t* obj_new = new world_cup_t();

    int permutations [5][5] =
            {
                    {1,3,4,2,0},
                    {0,1,2,4,3},
                    {2,0,4,3,1},
                    {1,2,0,3,4},
                    {4,3,0,1,2}
            };


    obj_new->add_team(100);
    obj_new->add_team(200);
    obj_new->add_team(300);
    obj_new->add_team(400);
    obj_new->add_team(500);
    obj_new->add_team(600);
    obj_new->add_team(700);
    obj_new->add_team(800);
    obj_new->add_team(900);
    obj_new->add_team(1000);


    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 8; ++j) {
            StatusType S = obj_new->add_player(i*100+j,i*100,permutations[(i+j)%5],i%5 + 8, (i+ j)%6, 0, true);
            if(S != StatusType::SUCCESS)
                cout<<"problem "<< i*100+j<<endl;
        }
    }

    obj_new->buy_team(200,100);
    obj_new->buy_team(300,200);
    obj_new->buy_team(400,300);
    obj_new->buy_team(500,400);
    obj_new->buy_team(600,500);
    obj_new->buy_team(700,600);
    obj_new->buy_team(800,700);


    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 10; ++j) {
            cout<<"player number: "<< i*100+j<<endl;
            cout<< obj_new->get_partial_spirit(i*100+j).ans()<<endl;
            cout<< obj_new->num_played_games_for_player(i*100+j).ans()<<endl;

        }
    }

    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 10; ++j) {
            cout<<"player number: "<< i*100+j<<endl;
            cout<< obj_new->get_partial_spirit(i*100+j).ans()<<endl;
            cout<< obj_new->num_played_games_for_player(i*100+j).ans()<<endl;

        }
    }


}
void test4(){

    world_cup_t* obj_new = new world_cup_t();

    int permutations [5][5] =
            {
                    {1,3,4,2,0},
                    {0,1,2,4,3},
                    {2,0,4,3,1},
                    {1,2,0,3,4},
                    {4,3,0,1,2}
            };


    obj_new->add_team(100);
    obj_new->add_team(200);
    obj_new->add_team(300);
    obj_new->add_team(400);
    obj_new->add_team(500);
    obj_new->add_team(600);
    obj_new->add_team(700);
    obj_new->add_team(800);
    obj_new->add_team(900);
    obj_new->add_team(1000);


    for(int i = 1; i<=8; i++){
        for (int j = 0; j < 8; ++j) {
            StatusType S = obj_new->add_player(i*100+j,i*100,permutations[(i+j)%5],i%5 + 8, (i+ j)%6, 0, true);
            if(S != StatusType::SUCCESS)
                cout<<"problem "<< i*100+j<<endl;
        }
    }
    StatusType S = obj_new->add_player(1000,100,permutations[3],8, 6, 0, true);


    obj_new->buy_team(200,100);
    obj_new->buy_team(300,400);
    obj_new->buy_team(200,300);


    cout<< obj_new->get_partial_spirit(205).ans()<<endl;
    cout<< obj_new->num_played_games_for_player(205).ans()<<endl;
    cout<< obj_new->get_partial_spirit(205).ans()<<endl;
    cout<< obj_new->num_played_games_for_player(205).ans()<<endl;
    cout<< obj_new->get_partial_spirit(200).ans()<<endl;
    cout<< obj_new->num_played_games_for_player(200).ans()<<endl;
    cout<< obj_new->get_partial_spirit(200).ans()<<endl;
    cout<< obj_new->num_played_games_for_player(200).ans()<<endl;
    cout<< obj_new->get_partial_spirit(103).ans()<<endl;
    cout<< obj_new->num_played_games_for_player(103).ans()<<endl;
    cout<< obj_new->get_partial_spirit(103).ans()<<endl;
    cout<< obj_new->num_played_games_for_player(103).ans()<<endl;

}



int main() {

    test1();
    test2();
    test3();
    test4();

    return 666;
}


