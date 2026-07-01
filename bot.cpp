#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int x, y;
    int fruits;
    string type;
    long long dist_sq;
    int index;

    bool operator<(const Tree& other) const {
        return dist_sq < other.dist_sq;
    }
};

int main()
{
    int width, height;
    cin >> width >> height;
    cin.ignore();

    int shkx = 0, shky = 0;

    // find shack
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line);

        for (int j = 0; j < line.size(); j++) {
            if (line[j] == '0') {
                shkx = j;
                shky = i;
            }
        }
    }

    // planting spots around shack — BOUNDS CHECKED
    vector<pair<int,int>> plant_spots;

    auto add_spot = [&](int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            plant_spots.push_back({x, y});
        }
    };

    add_spot(shkx + 1, shky);
    add_spot(shkx - 1, shky);
    add_spot(shkx, shky + 1);
    add_spot(shkx, shky - 1);

    int planted = 0;
    string saved_tree_type = "PLUM";

    while (1)
    {
        // inventories
        int my_plums, my_lemons, my_apples, my_bananas, res1, res2;
        cin >> my_plums >> my_lemons >> my_apples >> my_bananas >> res1 >> res2;
        cin.ignore();

        int opp_plums, opp_lemons, opp_apples, opp_bananas, res3, res4;
        cin >> opp_plums >> opp_lemons >> opp_apples >> opp_bananas >> res3 >> res4;
        cin.ignore();

        // trees
        int trees_count;
        cin >> trees_count;
        cin.ignore();

        vector<Tree> trees;

        for (int i = 0; i < trees_count; i++) {
            string type;
            int x, y, size, health, fruits, cooldown;

            cin >> type >> x >> y >> size >> health >> fruits >> cooldown;
            cin.ignore();

            if (fruits > 0) {
                trees.push_back({x, y, fruits, type, 0, i});
            }
        }

        // trolls
        int trolls_count;
        cin >> trolls_count;
        cin.ignore();

        vector<pair<int, pair<int, int>>> my_trolls;
        map<int, int> troll_carry;

        for (int i = 0; i < trolls_count; i++) {

            int id, player, x, y;
            int movement_speed, carry_capacity, harvest_power, chop_power;
            int carry_plum, carry_lemon, carry_apple, carry_banana;
            int res5, res6;

            cin >> id >> player >> x >> y
                >> movement_speed >> carry_capacity
                >> harvest_power >> chop_power
                >> carry_plum >> carry_lemon
                >> carry_apple >> carry_banana
                >> res5 >> res6;

            cin.ignore();

            if (player == 0) {

                int carry =
                    carry_plum +
                    carry_lemon +
                    carry_apple +
                    carry_banana;

                my_trolls.push_back({id, {x, y}});
                troll_carry[id] = carry;
            }
        }

        sort(my_trolls.begin(), my_trolls.end());

        vector<string> commands;

        // =====================================================================
        // FIRST TROLL = PLANTER
        // =====================================================================

        if (!my_trolls.empty())
        {
            int troll_id = my_trolls[0].first;
            int troll_x = my_trolls[0].second.first;
            int troll_y = my_trolls[0].second.second;
            int carry = troll_carry[troll_id];

            string command = "WAIT";

            // plant trees around shack first
            if (planted < (int)plant_spots.size())
            {
                int tx = plant_spots[planted].first;
                int ty = plant_spots[planted].second;

                // carrying fruit -> go plant
                if (carry > 0)
                {
                    if (troll_x == tx && troll_y == ty)
                    {
                        command =
                            "PLANT " +
                            to_string(troll_id) + " " +
                            saved_tree_type;

                        planted++;
                    }
                    else
                    {
                        command =
                            "MOVE " +
                            to_string(troll_id) + " " +
                            to_string(tx) + " " +
                            to_string(ty);
                    }
                }

                // no fruit -> collect fruit first
                else if (!trees.empty())
                {
                    for (auto &tree : trees) {
                        long long dx = tree.x - troll_x;
                        long long dy = tree.y - troll_y;
                        tree.dist_sq = dx * dx + dy * dy;
                    }

                    sort(trees.begin(), trees.end());

                    Tree &nearest_tree = trees[0];

                    if (troll_x == nearest_tree.x &&
                        troll_y == nearest_tree.y)
                    {
                        command =
                            "HARVEST " +
                            to_string(troll_id);

                        saved_tree_type = nearest_tree.type;
                    }
                    else
                    {
                        command =
                            "MOVE " +
                            to_string(troll_id) + " " +
                            to_string(nearest_tree.x) + " " +
                            to_string(nearest_tree.y);
                    }
                }
            }

            // after planting -> normal harvesting
            else
            {
                if (carry > 0)
                {
                    int dist_to_shack =
                        abs(troll_x - shkx) +
                        abs(troll_y - shky);

                    if (dist_to_shack <= 1)
                    {
                        command =
                            "DROP " +
                            to_string(troll_id);
                    }
                    else
                    {
                        command =
                            "MOVE " +
                            to_string(troll_id) + " " +
                            to_string(shkx) + " " +
                            to_string(shky);
                    }
                }

                else if (!trees.empty())
                {
                    for (auto &tree : trees) {
                        long long dx = tree.x - troll_x;
                        long long dy = tree.y - troll_y;
                        tree.dist_sq = dx * dx + dy * dy;
                    }

                    sort(trees.begin(), trees.end());

                    Tree &nearest_tree = trees[0];

                    if (troll_x == nearest_tree.x &&
                        troll_y == nearest_tree.y)
                    {
                        command =
                            "HARVEST " +
                            to_string(troll_id);
                    }
                    else
                    {
                        command =
                            "MOVE " +
                            to_string(troll_id) + " " +
                            to_string(nearest_tree.x) + " " +
                            to_string(nearest_tree.y);
                    }
                }
            }

            commands.push_back(command);
        }

        // =====================================================================
        // OTHER TROLLS = NORMAL HARVESTERS
        // =====================================================================

        for (int t = 1; t < my_trolls.size(); t++)
        {
            int troll_id = my_trolls[t].first;
            int troll_x = my_trolls[t].second.first;
            int troll_y = my_trolls[t].second.second;
            int carry = troll_carry[troll_id];

            string command = "WAIT";

            // return resources
            if (carry > 0)
            {
                int dist_to_shack =
                    abs(troll_x - shkx) +
                    abs(troll_y - shky);

                if (dist_to_shack <= 1)
                {
                    command =
                        "DROP " +
                        to_string(troll_id);
                }
                else
                {
                    command =
                        "MOVE " +
                        to_string(troll_id) + " " +
                        to_string(shkx) + " " +
                        to_string(shky);
                }
            }
            // harvest nearest tree
            else if (!trees.empty())
            {
                vector<Tree> troll_trees = trees;

                for (auto &tree : troll_trees) {
                    long long dx = tree.x - troll_x;
                    long long dy = tree.y - troll_y;
                    tree.dist_sq = dx * dx + dy * dy;
                }

                sort(troll_trees.begin(), troll_trees.end());

                Tree &nearest_tree = troll_trees[0];

                if (troll_x == nearest_tree.x &&
                    troll_y == nearest_tree.y)
                {
                    command =
                        "HARVEST " +
                        to_string(troll_id);
                }
                else
                {
                    command =
                        "MOVE " +
                        to_string(troll_id) + " " +
                        to_string(nearest_tree.x) + " " +
                        to_string(nearest_tree.y);
                }
            }

            commands.push_back(command);
        }
        if (my_trolls.size() < 3)
        {
            int num_trolls = my_trolls.size();

            int cost_movement = num_trolls + 1;
            int cost_carry = num_trolls + 1;
            int cost_harvest = num_trolls + 1;

            if (my_plums >= cost_movement &&
                my_lemons >= cost_carry &&
                my_apples >= cost_harvest)
            {
                commands.push_back("TRAIN 2 1 1 0");
            }
        }
        for (int i = 0; i < commands.size(); i++) {
            cout << commands[i];

            if (i + 1 < commands.size())
                cout << ";";
        }

        cout << endl;
    }

    return 0;
}
