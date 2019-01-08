#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

/****************************
 * CnfSatVc class definition
 ****************************/
class CnfSatVc
{
private:
    Logger logger;
    std::vector< std::pair<unsigned,unsigned> > edges;
    std::size_t vertex_count = 0;
    std::string vertex_cover = "";
    std::string vc_output = "";
    int vc_count = 0;

    bool minisatCheck(int k, int n);
    bool binarySearch( int min, int max );

public:
    CnfSatVc(Logger logger, std::size_t vertex_count, std::vector< std::pair<unsigned,unsigned> > edges);
    void getResults(vc_return *results);
    void debugOn();
};

/****************************
 * CnfSatVc class implementation
 ****************************/
CnfSatVc::CnfSatVc(Logger logger, std::size_t vertex_count, std::vector< std::pair<unsigned,unsigned> > edges)
{
    this->logger = logger;
    this->vertex_count = vertex_count;
    this->edges = edges;
    this->binarySearch(0,vertex_count-1);
}

void CnfSatVc::getResults(vc_return *results)
{
    results->vc_output = this->vc_output;
    results->vc_count = this->vc_count;
}

void CnfSatVc::debugOn()
{
    this->logger.debugOn();
}

bool CnfSatVc::minisatCheck(int k, int n)
{
    int a_count = (n*k);
    std::vector< int > clause;

    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    Minisat::Lit lits[a_count+1]; //0 index ignored

    for(int i=1; i <= a_count; i++)
    {
        lits[i] = Minisat::mkLit(solver->newVar());
    }

    // (1)
    this->logger.printDebug("-------------------");
    clause.clear();
    for(int i=0; i < k; i++)
    {
        Minisat::vec<Minisat::Lit> clause;
        for(int j=i+1; j <= a_count; j=j+k)
        {
            clause.push( lits[j] );
            this->logger.printDebug( std::to_string(j) + " ", false );
        }
        solver->addClause(clause);
        this->logger.printDebug("0");
    }

    // (2a)
    this->logger.printDebug("-------------------");
    int max_j = k;
    for(int i=1; i <= a_count; i++)
    {
        if( i % k == 0 )
        {
            max_j = max_j + k;
            continue;
        }

        for(int j=i+1; j <= max_j; j++)
        {
            Minisat::vec<Minisat::Lit> clause;
            clause.push( ~lits[i] );
            clause.push( ~lits[j] );
            solver->addClause(clause);
            this->logger.printDebug( "-" + std::to_string(i) + " -" + std::to_string(j) + " 0" );
        }
    }

    // (2b)
    for(int i=1; i <= k; i++)
    {
        for(int j=i; j <= a_count; j=j+k)
        {
            for(int h=j+k; h <= a_count; h=h+k)
            {
                Minisat::vec<Minisat::Lit> clause;
                clause.push( ~lits[j] );
                clause.push( ~lits[h] );
                solver->addClause(clause);
                this->logger.printDebug( "-" + std::to_string(j) + " -" + std::to_string(h) + " 0" );
            }
        }
    }

    // (3)
    this->logger.printDebug("-------------------");
    for( unsigned i=0; i < edges.size(); i++)
    {
        Minisat::vec<Minisat::Lit> clause;
        int first, second;
        if (edges[i].first < edges[i].second )
        {
            first  = edges[i].first + 1;
            second = edges[i].second + 1;
        }
        else
        {
            first  = edges[i].second + 1;
            second = edges[i].first + 1;
        }
        for(int j=0; j<k; j++)
        {
            int g = ( (second-1)*k + 1 + j);
            int h = ( (first-1)*k + 1 + j);
            clause.push( lits[g] );
            clause.push( lits[h] );
            this->logger.printDebug(std::to_string(g) + " " + std::to_string(h) + " ", false);
        }
        solver->addClause(clause);
        this->logger.printDebug("0");
    }

    // (4)
    this->logger.printDebug("-------------------");
    bool res = (solver->solve() == 1);
    if(res)
    {
        this->logger.printDebug("SATISFIED");

        this->vertex_cover = "";
        this->vc_count = 0;
        std::string prefix = "";
        int offset = 1;
        for(int i=1; i<=a_count; i++)
        {
            if( Minisat::toInt( solver->modelValue(lits[i]) )== 0)
            {
                this->vc_count++;
                this->vertex_cover.append(prefix);
                this->vertex_cover.append( std::to_string(i-offset) );
                prefix = ",";
            }
            if( i % k > 0 )
            {
                offset++;
            }
        }
        this->logger.printDebug( this->vertex_cover );
    }
    else
    {
        this->logger.printDebug("UNSATISFIED");
    }

    return res;
}


bool CnfSatVc::binarySearch( int min, int max )
{
    static int last_match = -1;

    this->logger.printDebug("+++++++++++++++++++++++++++++++++++++++");
    if(min > max)
    {
        this->logger.printDebug( "STOP: min = " +  std::to_string(min) + "; max = " +  std::to_string(max) + "; Last Match at k = " + std::to_string(last_match) );
        this->logger.printDebug("+++++++++++++++++++++++++++++++++++++++");
        return false;
    }

    int n = this->vertex_count;
    int e = this->edges.size();
    int k = (min + max)/2;
    int a = n * k;
    int c = k + (n * (k * (k-1))/2)  + (k * (n * (n-1))/2) + e;

    this->logger.printDebug( "n = "    + std::to_string(n) );
    this->logger.printDebug( "e = "    + std::to_string(e) );
    this->logger.printDebug( "min = "  + std::to_string(min) );
    this->logger.printDebug( "max = "  + std::to_string(max) );
    this->logger.printDebug( "k = "    + std::to_string(k) );
    this->logger.printDebug( "a = "    + std::to_string(a) );
    this->logger.printDebug( "c = "    + std::to_string(c) );

    if( k > 0 && this->minisatCheck(k, n) )
    {
        max = k - 1;
        last_match = k;
        if (this->binarySearch(min, max))
        {
            return true;
        }
        else if(this->vertex_cover != "")
        {
            this->vc_output = "CNF-SAT-VC: " + this->vertex_cover;
            this->vertex_cover = "";
        }
        return true;
    }
    else
    {
        min = k + 1;
        return this->binarySearch(min, max);
    }

}
