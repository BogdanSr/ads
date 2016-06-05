//
//  main_lngpok.cpp
//  Numbers
//
//  Created by Bogdan Shubravyi on 4/26/16.
//  Copyright © 2016 Bogdan Shubravyi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>
#include <iomanip>
#include <iterator>

#include <unistd.h>

using namespace std;

class Vertex;

class Edge
{
public:
    void print();
    
    Vertex *start;
    Vertex *end;
    
    Edge(Vertex *start, Vertex *end)
    {
        this->start = start;
        this->end = end;
    }
};

class Vertex
{
public:
    
    string label;
    vector<Edge *> *out_edges;
    vector<Edge *> *in_edges;
    
    int in_counter = 0;
    
    Vertex(string label)
    {
        this->label = label;
        this->out_edges = new vector<Edge*>();
        this->in_edges  = new vector<Edge*>();
    }
    
    void print()
    {
        for (int i = 0; i < out_edges->size(); ++i)
        {
            Edge *e = out_edges->at(i);
            
            e->print();
            
        }
    }
};

void Edge::print()
{
    cout<<this->start->label<<" -- > -- "<<this->end->label<<endl;
}

class Graph
{
    public:
    
    vector<Vertex*> *vertices;
    vector<Edge*> *edges;
    
    Graph(vector<Vertex*> *vertices, vector <Edge*> *edges)
    {
        this->vertices = vertices;
        this->edges = edges;
    }
    
    void print_vertices()
    {
        for (int i = 0; i < this->vertices->size(); ++i)
        {
            Vertex *vertex = vertices->at(i);
            
            vertex->print();
        }
    }
};


inline Vertex *get_vertex(string label, map<string, Vertex*> *vertices_map, vector<Vertex *> *vertices)
{
    Vertex *result;
    
    map<string, Vertex*>::iterator it;
    
    it = vertices_map->find(label);
    
    if(it != vertices_map->end()) {
        result = (*it).second;
    }
    else {
        result = new Vertex(label);
        vertices_map->insert(make_pair(label, result));
        vertices->push_back(result);
    }
    return result;
}

Graph *get_data()
{
    std::ifstream in("govern.in");
    
    std::vector<string> lines{ std::istream_iterator<string>(in),
        std::istream_iterator<string>() };
    
    map<string, Vertex*> *vertices_map = new map<string, Vertex*>();
    vector<Vertex *> *vertices = new vector<Vertex*>();
    vector<Edge*> *edges = new vector<Edge*>();
    
    map<string, Vertex*>::iterator it;
    Vertex *start_vertex;
    Vertex *end_vertex;
    Edge *edge;
    
    for (int i=0; i<lines.size(); i++)
    {
        if (i % 2 == 0) {
            continue;
        }
        
        string start_label = lines[i - 1];
        string   end_label = lines[i];
        
        start_vertex = get_vertex(start_label, vertices_map, vertices);
        end_vertex   = get_vertex(end_label, vertices_map, vertices);
        
        edge = new Edge(start_vertex, end_vertex);
        
        edges->push_back(edge);
        
        start_vertex->out_edges->push_back(edge);
        end_vertex->in_edges->push_back(edge);
        
        end_vertex->in_counter += 1;
    }
    
    Graph *graph = new Graph(vertices, edges);
    
    return graph;
}

vector<Vertex *> *topological_sort(Graph *graph)
{
    vector<Vertex *> *result = new vector<Vertex *>();

    std::queue<Vertex *> queue;
    
    for (int i = 0; i < graph->vertices->size(); ++i)
    {
        Vertex *vertex = graph->vertices->at(i);
        
        if (vertex->in_counter == 0) {
            queue.push(vertex);
        }
    }
    
    while (queue.size() > 0) {
        
        Vertex *vertex = queue.front();
        queue.pop();
        
        result->push_back(vertex);
        
        for (int i = 0; i < vertex->out_edges->size(); ++i) {
            
            Edge *edge = vertex->out_edges->at(i);
            
            Vertex *end_vertex = edge->end;
            
            end_vertex->in_counter -= 1;
            
            if (end_vertex->in_counter == 0) {
                queue.push(end_vertex);
            }
        }
    }
    
    return result;
}

int main(int argc, const char * argv[])
{
    Graph *graph = get_data();

    vector<Vertex *> *result = topological_sort(graph);
    
    ofstream output;
    output.open ("govern.out");
    
    for (int i = result->size() - 1; i >= 0; i--) {
        output<<result->at(i)->label<<endl;
    }

    output.close();
    
    return 0;
}

