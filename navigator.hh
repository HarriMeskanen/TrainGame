#ifndef NAVIGATOR_HH
#define NAVIGATOR_HH

#include "trafficplace.hh"
#include "other.hh"
#include <iostream>
#include <QVector>
#include <QMap>

/**
 * @brief The Node struct links its object TrafficPlace to the shortest distance
 * leading to it and to the previous node on the path.
 */
struct Node{

     /** @brief parent Node is the previous Node on the path*/
    Node* parent;

    /** @brief object represents the current TrafficPlace*/
    TrafficPlace* object;

    /** @brief distance tells the length of shortest path leading to
        this node*/
    double distance;
};

/** @brief The Navigator class is used to determine playerTrain's path*/
class Navigator
{
public:
    Navigator();

    /** @brief navigate method
     * @return true if path from startpoint to endpoint exists*/
    bool navigate(TrafficPlace* start, TrafficPlace* end);

    /** @brief path moves through the linked list of Nodes
     * @return path returns a vector containing shortest route to endNode*/
    QVector<TrafficPlace*> path();

    void initNewNavigation(TrafficPlace* start, TrafficPlace* end);
    void search();
    void reset();
    void emptyUnFinished();
    void emptyBlackListed();

    void createNode(TrafficPlace* object);
    void updateNode(Node* node);
    void updateEndNode();
    void updateContainers(); 
    Node* findShortestUnFinished();

private:    
    QMap<QString, Node*> unFinished_;
    QMap<QString, Node*> blackListed_;

    Node* current_ = 0;
    Node* endNode_ = 0;

    TrafficPlace* start_;
    TrafficPlace* end_;
};

#endif // NAVIGATOR_HH
