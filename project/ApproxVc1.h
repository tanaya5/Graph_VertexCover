/*****************************
  class declaration
***************************/
class ApproxVc1
{
private:
    Logger logger;
    bool *vc;
    std::vector< std::pair<unsigned,unsigned> > edges;
    std::string vc_output = "";
    int vc_count = 0;

    void addToVC(unsigned vertex);
    void outputVC(unsigned vertex_count);

public:
    ApproxVc1(Logger logger, unsigned vertex_count, std::vector< std::pair<unsigned,unsigned> > edges);
    void getResults(vc_return *results);
};

//constructor
ApproxVc1::ApproxVc1(Logger logger, unsigned vertex_count, std::vector< std::pair<unsigned,unsigned> > edges)
{
    //initialize important variables
    this->logger = logger;
    this->edges = edges;
    bool cover[vertex_count];
    for(unsigned i=0; i<vertex_count; i++)
    {
        cover[i] = false;
    }
    this->vc = cover;

    //initialize adjacency list
    std::list<unsigned> adjacency_list[vertex_count];
    for(unsigned i=0; i < edges.size(); i++)
    {
        adjacency_list[ edges[i].first ].push_back( edges[i].second );
        adjacency_list[ edges[i].second ].push_back( edges[i].first );
    }

    //initialize degrees for all vertex
    std::list<unsigned> degrees[vertex_count];
    for(unsigned i=0; i < vertex_count; i++)
    {
        int degree = adjacency_list[i].size();
        degrees[degree].push_back(i);
    }

    //find vertex cover iterating from highest degree to lowest
    for(unsigned i=vertex_count-1; i>0; i--)
    {
        this->logger.printDebug("Degree '" + std::to_string(i) + "' has nodes =", false);
        for(unsigned vertex : degrees[i])
        {
            if(this->edges.size()>0)
            {
                this->addToVC(vertex);
            }
            this->logger.printDebug(" " + std::to_string(vertex), false);
        }
        this->logger.printDebug("");
    }

    //Output vertex cover
    this->outputVC(vertex_count);
}

//if vertex qualifies, save to vertex cover
void ApproxVc1::addToVC(unsigned vertex)
{
    std::vector< std::pair<unsigned,unsigned> > new_edges;

    for(unsigned i=0; i<this->edges.size(); i++)
    {
        if(vertex == this->edges[i].first || vertex == this->edges[i].second)
        {
            this->vc[vertex] = true;
        }
        else
        {
            new_edges.push_back(this->edges[i]);
        }
    }
    this->edges = new_edges;
}

//output an ordered vertex cover
void ApproxVc1::outputVC(unsigned vertex_count)
{
    std::string prefix = " ";
    this->vc_count = 0;
    this->vc_output = "APPROX-VC-1:";
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

void  ApproxVc1::getResults(vc_return *results)
{
    results->vc_output = this->vc_output;
    results->vc_count = this->vc_count;
}
