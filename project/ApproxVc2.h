/*****************************
  class declaration
***************************/
class ApproxVc2
{
private:
    Logger logger;
    bool *vc;
    std::vector< std::pair<unsigned,unsigned> > edges;
    std::string vc_output = "";
    int vc_count = 0;

    void addToVC(std::pair<unsigned,unsigned>);
    void outputVC(unsigned vertex_count);
    std::pair<unsigned,unsigned> randomEdge();

public:
    ApproxVc2(Logger logger, unsigned vertex_count, std::vector< std::pair<unsigned,unsigned> > edges);
    void getResults(vc_return *results);
};

//constructor
ApproxVc2::ApproxVc2(Logger logger, unsigned vertex_count, std::vector< std::pair<unsigned,unsigned> > edges)
{
    //initialize important variables
    srand (time(NULL));
    this->logger = logger;
    this->edges = edges;
    bool cover[vertex_count];
    for(unsigned i=0; i<vertex_count; i++)
    {
        cover[i] = false;
    }
    this->vc = cover;

    //Randomly pick edge and add to VC
    while( this->edges.size()> 0 )
    {
        this->addToVC( this->randomEdge() );
    }

    //Output vertex cover
    this->outputVC(vertex_count);
}

//if vertex qualifies, save to vertex cover
void ApproxVc2::addToVC(std::pair<unsigned,unsigned> edge)
{
    std::vector< std::pair<unsigned,unsigned> > new_edges;

    for(unsigned i=0; i<this->edges.size(); i++)
    {
        if( edge.first == this->edges[i].first || edge.first == this->edges[i].second ||
                edge.second == this->edges[i].first || edge.second == this->edges[i].second)
        {
            this->vc[edge.first] = true;
            this->vc[edge.second] = true;
        }
        else
        {
            new_edges.push_back(this->edges[i]);
        }
    }
    this->edges = new_edges;
}

//output an ordered vertex cover
void ApproxVc2::outputVC(unsigned vertex_count)
{
    std::string prefix = " ";
    this->vc_count = 0;
    this->vc_output = "APPROX-VC-2:";
    for(unsigned i=0; i<vertex_count; i++)
    {
        if(this->vc[i])
        {
            this->vc_count++;
            this->vc_output.append(prefix + std::to_string(i));
            prefix = ",";
        }
    }
}

std::pair<unsigned,unsigned> ApproxVc2::randomEdge()
{
    unsigned edge_count = this->edges.size();
    if(edge_count < 1)  throw "Random edge requested on an empty list.";

    unsigned i = std::rand() % edge_count;
    this->logger.printDebug("VC2: random edge #" + std::to_string(i) + " out of 0 - " + std::to_string(edge_count - 1) );
    return this->edges[i];
}

void  ApproxVc2::getResults(vc_return *results)
{
    results->vc_output = this->vc_output;
    results->vc_count = this->vc_count;
}
