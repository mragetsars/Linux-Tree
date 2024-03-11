#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <sstream>

#define Space "   "
#define OrSpace "|  "
#define OrUnderline "|__"

using namespace std;

struct item_struct
{
    vector<string> item_name;
    vector<int> item_root;
};

item_struct input_receiver(int sizeof_input)
{
    item_struct output;
    if (sizeof_input > 0)
    {
        int temporary_int;
        string temporary_string;
        while (sizeof_input > 0)
        {
            cin >> temporary_string;
            output.item_name.push_back(temporary_string);
            cin >> temporary_int;
            output.item_root.push_back(temporary_int);
            sizeof_input--;
        }
    }
    else
    {
        cout << "\n INPUT ERROR!";
    }
    return output;
}

int depth_calculator(int i, item_struct input)
{
    if (i > 0)
    {
        return 1 + depth_calculator(input.item_root[i] - 1, input);
    }
    else
    {
        return 0;
    }
}

vector<int> depth_generator(int sizeof_input, item_struct input, vector<int> output_depth)
{
    sizeof_input--;
    if (sizeof_input > 0)
    {
        output_depth[sizeof_input] = depth_calculator(sizeof_input, input);
        return depth_generator(sizeof_input, input, output_depth);
    }
    else
    {
        output_depth[sizeof_input] = 1;
        return output_depth;
    }
}

int tree_editor(int i, int size, vector<int> input_depth, int n)
{
    int r = 0;
    for (int x = i; x < size; x++)
    {
        if (n == input_depth[x])
        {
            for (int y = 1; y < x - i; y++)
            {
                if (input_depth[x - y] < input_depth[x])
                {
                    return 0;
                }
            }
            if (r == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

void tree_printer(int i, item_struct input, int depthof_input, vector<int> input_depth)
{
    cout << "\n";
    for (int i = 0; i < input.item_name.size(); i++)
    {
        if ((i < input.item_name.size()) && (depthof_input >= input_depth[i]))
        {
            for (int n = 1; n < input_depth[i]; n++)
            {
                if (tree_editor(i, input.item_name.size(), input_depth, n))
                {
                    cout << OrSpace;
                }
                else
                {
                    cout << Space;
                }
            }
            cout << OrUnderline << input.item_name[i] << '\n';
        }
    }
}

int main()
{
    int sizeof_items;
    int depthof_items;
    cin >> sizeof_items;
    cin >> depthof_items;

    item_struct item_input = input_receiver(sizeof_items);

    vector<int> item_depth(sizeof_items);
    item_depth = depth_generator(sizeof_items, item_input, item_depth);

    int i;
    tree_printer(i, item_input, depthof_items, item_depth);
    return 0;
}