
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

struct concat1
{    
    typedef std::string type;
    
    template<typename Sig>
    struct result
    {
        typedef std::string type;
    };
    
    std::string operator()(const std::string& a1) const
    { 
        return std::string(__FUNCTION__) + ": " + a1; 
    }
};


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

struct concat3
{    
    typedef std::string type;
    
    template<typename Sig>
    struct result
    {
        typedef std::string type;
    };
    
    std::string operator()(const std::string& a1
                           , const std::string& a2
                           , const std::string& a3) const
    { 
        return std::string(__FUNCTION__) + ": " + a1+"|"+a2+"|"+a3; 
    }
};

struct concat4
{    
    typedef std::string type;
    
    template<typename Sig>
    struct result
    {
        typedef std::string type;
    };
    
    std::string operator()(const std::string& a1
                           , const std::string& a2
                           , const std::string& a3
                           , const std::string& a4) const
    { 
        return std::string(__FUNCTION__) + ": " + a1+"|"+a2+"|"+a3+"|"+a4; 
    }
};

struct concat5 
{    
    typedef std::string type;
    
    template<typename Sig>
    struct result
    {
        typedef std::string type;
    };
    
    std::string operator()(const std::string& a1
                           , const std::string& a2
                           , const std::string& a3
                           , const std::string& a4
                           , const std::string& a5) const
    { 
        return std::string(__FUNCTION__) + ": " + a1+"|"+a2+"|"+a3+"|"+a4+"|"+a5; 
    }
};

struct repeat
{    
    repeat(int n=2)
    : number(n)
    {}
    
    typedef std::string type;
    
    template<typename Sig>
    struct result
    {
        typedef std::string type;
    };
    
    std::string operator()(const std::string& a1) const
    { 
        std::string out;
        for (int i=0;i<number;i++)
            out += a1;
        return out;
    }
private:
    int number;
 //   repeat(const repeat& that);
};


int main()
{
    std::cout << "hello!" << std::endl;

    operator_strops_unit_tests().Run();

    std::cout << "Unit tests passed!" << std::endl;

    //return 0;
    
    DataSource<std::string>* dataSource1(new DataSource<std::string>("DataSource1"));
    boost::shared_ptr<Strop<std::string()> > strop1(dataSource1);
    proto::terminal<const boost::shared_ptr<Strop<std::string()> > >::type strop_term1 = {strop1};

    DataSource<std::string>* dataSource2(new DataSource<std::string>("DataSource2"));        
    boost::shared_ptr<Strop<std::string()> > strop2(dataSource2);
    proto::terminal<const boost::shared_ptr<Strop<std::string()> > >::type strop_term2 = {strop2};
    
    boost::shared_ptr<Const<std::string> > source3(new Const<std::string>("hello"));

        
    Engine streamulus;

        

    streamulus.Subscribe(Streamify<concat3>(strop1,strop2,source3));


#if 0    
    streamulus.Subscribe(Streamify<concat1>(strop1));
    streamulus.Subscribe(Streamify<concat2>(strop1,strop1));
    streamulus.Subscribe(Streamify<concat3>(strop1,strop1,strop1));
    streamulus.Subscribe(Streamify<concat4>(strop1,strop1,strop1,strop1));
    streamulus.Subscribe(Streamify<concat5>(strop1,strop1,strop1,strop1,strop1));
#endif 
    
//    streamulus.Subscribe(strop_term1+Streamify<plus_func>(Streamify<plus_func>(strop_term1, strop_term2),strop_term1));
    

	std::cout << "descriptor 1 = " << strop1->Descriptor() << std::endl;
	std::cout << "descriptor 2 = " << strop2->Descriptor() << std::endl;

#if 1
    std::vector<int> ticks;
    ticks.push_back(1);
    ticks.push_back(2);
    ticks.push_back(3);
    for (std::vector<int>::const_iterator it = ticks.begin(); it != ticks.end(); ++it)
    {
        std::stringstream ss1;
        std::stringstream ss2;
        ss1 << *it;
        ss2 << 2*(*it);
        std::cout << "Tick 1 " << ss1.str() << std::endl;
        dataSource1->Tick(ss1.str());

// TODO: fix bug. crashes when ticking on a strop that wasn't used in an expression      
//        std::cout << "Tick 2 " << ss2.str() << std::endl;
        dataSource2->Tick(ss2.str());
    
        getchar();
    }
#endif  		
	getchar();
    return 0;
}
