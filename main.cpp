
#include "stream.h"
#include "strop.h"
#include "const.h"
#include "data_source.h"
#include "func.h"
#include "operators.h"
#include "engine.h"

#include "streamify.h"

#include <boost/mpl/vector.hpp>
#include <boost/mpl/assert.hpp>


using namespace streamulus;

struct concat2
{    
    typedef std::string type;
    
    template<typename Sig>
    struct result
    {
        typedef std::string type;
    };
    
    std::string operator()(const std::string& a1
                           , const std::string& a2) const
    { 
        return std::string(__FUNCTION__) + ": " + a1+"|"+a2; 
    }
};


// a little test harness for dev. Nothing too planned.
int main()
{
    std::cout << "hello!" << std::endl;

    operator_strops_unit_tests().Run();

    std::cout << "Unit tests passed!" << std::endl;
        
    DataSource<double>* dataSource1(new DataSource<double>("DoubleInput1"));
    boost::shared_ptr<Strop<double()> > strop1(dataSource1);
    proto::terminal<const boost::shared_ptr<Strop<double()> > >::type strop_term1 = {strop1};

    DataSource<double>* dataSource2(new DataSource<double>("DoubleInput2"));        
    boost::shared_ptr<Strop<double()> > strop2(dataSource2);
    proto::terminal<const boost::shared_ptr<Strop<double()> > >::type strop_term2 = {strop2};
    
    DataSource<std::string>* stringDataSource1(new DataSource<std::string>("StringInput1"));        
    boost::shared_ptr<Strop<std::string()> > sstrop1(stringDataSource1);
    proto::terminal<const boost::shared_ptr<Strop<std::string()> > >::type sstrop_term1 = {sstrop1};

    DataSource<std::string>* stringDataSource2(new DataSource<std::string>("StringInput2"));        
    boost::shared_ptr<Strop<std::string()> > sstrop2(stringDataSource2);
    proto::terminal<const boost::shared_ptr<Strop<std::string()> > >::type sstrop_term2 = {sstrop2};
    
//    boost::shared_ptr<Const<std::string> > source3(new Const<std::string>("hello"));

        
    Engine streamulus;        

    streamulus.Subscribe(strop_term1/(strop_term1+strop_term2));


    streamulus.Subscribe(Streamify<concat2>(sstrop1,sstrop2));
    
//    streamulus.Subscribe(strop_term1+Streamify<plus_func>(Streamify<plus_func>(strop_term1, strop_term2),strop_term1));
    

#if 1
    std::vector<double> ticks;
    ticks.push_back(1);
    ticks.push_back(2);
    ticks.push_back(3);
    for (std::vector<double>::const_iterator it = ticks.begin(); it != ticks.end(); ++it)
    {
        std::cout << "Tick 1 " << *it << std::endl;
        dataSource1->Tick(*it);

// TODO: fix bug. crashes when ticking on a strop that wasn't used in an expression      
//        std::cout << "Tick 2 " << ss2.str() << std::endl;
        dataSource2->Tick((*it)*(*it));

        std::stringstream ss1;
        ss1 << *it;
        stringDataSource1->Tick(ss1.str());

        std::stringstream ss2;
        ss2 << (*it)*(*it);
        stringDataSource2->Tick(ss2.str());
        
        getchar();
    }
#endif  		
	getchar();
    return 0;
}
