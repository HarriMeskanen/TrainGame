#include "navigator.hh"

Navigator::Navigator()
{

}

bool Navigator::navigate(TrafficPlace *start, TrafficPlace *end)
{
    initNewNavigation(start, end);
    search();
    if(endNode_)
        return true;
    else return false;
}

void Navigator::initNewNavigation(TrafficPlace* start, TrafficPlace* end)
{
    reset();

    start_ = start;
    end_ = end;

    Node* node = new Node{
        0,
        start,
        0
    };
    current_ = node;
    unFinished_.insert(node->object->stationShortCode(), node);
}

void Navigator::search()
{
    if(unFinished_.empty())
        return;

    for(unsigned int i = 0; i < current_->object->neighbours().size(); i++)
    {
        TrafficPlace* child = current_->object->neighbours().at(i);

        if(blackListed_.contains(child->stationShortCode()))
            continue;

        if(endNode_){
            if(child == endNode_->object){
                updateEndNode();
                continue;
            }
        }
        if(!unFinished_.contains(child->stationShortCode()))
            createNode(child);

        else
            updateNode(unFinished_.value(child->stationShortCode()));
    }
    updateContainers();
    search();
}

void Navigator::createNode(TrafficPlace *object)
{
    Node* node = new Node{
        current_,
        object,
        current_->distance + MATHFUNCTIONS::distanceFromObject(current_->object, object)
    };
    if(object != end_)
        unFinished_.insert(node->object->stationShortCode(), node);
    else{

        endNode_ = node;
    }
}

void Navigator::updateNode(Node* node)
{
    double distanceThroughCurrent = current_->distance +
            MATHFUNCTIONS::distanceFromObject(current_->object, node->object);

    if(distanceThroughCurrent < node->distance){
        node->parent = current_;
        node->distance = distanceThroughCurrent;
    }
}

void Navigator::updateEndNode()
{
    double distanceThroughCurrent = current_->distance +
           MATHFUNCTIONS::distanceFromObject(current_->object, endNode_->object);

    if(distanceThroughCurrent < endNode_->distance){
        endNode_->parent = current_;
        endNode_->distance = distanceThroughCurrent;
    }
}

void Navigator::updateContainers()
{
    unFinished_.remove(current_->object->stationShortCode());
    blackListed_.insert(current_->object->stationShortCode(), current_);
    current_ = findShortestUnFinished();

    if(current_ && endNode_){
        if(current_->distance >= endNode_->distance){
            emptyUnFinished();
        }
    }
}

Node* Navigator::findShortestUnFinished()
{
    Node* shortest = 0;

    for(auto iter = unFinished_.begin(); iter != unFinished_.end(); iter++)
    {
        if(!shortest)
            shortest = iter.value();
        else{
            if(iter.value()->distance < shortest->distance)
                shortest = iter.value();
        }
    }
    return shortest;
}

QVector<TrafficPlace*> Navigator::path()
{
    QVector<TrafficPlace*> path;
    Node* node = endNode_;

    while(node->object != start_)
    {
            path.push_back(node->object);
            node = node->parent;
    }

    QVector<TrafficPlace*> thePath;
    thePath.push_back(start_);

    while(!path.empty())
    {
        thePath.push_back(path.last());
        path.removeLast();
    }

    return thePath;
}

void Navigator::reset()
{
    emptyUnFinished();
    emptyBlackListed();

    if(endNode_){
        delete endNode_;
        endNode_ = 0;
    }
    start_ = 0;
    end_ = 0;
}

void Navigator::emptyUnFinished()
{
    qDeleteAll(unFinished_);
    unFinished_.clear();
}

void Navigator::emptyBlackListed()

{
    qDeleteAll(blackListed_);
    blackListed_.clear();
}
