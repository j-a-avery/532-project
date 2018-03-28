#include <vector>
#include <atomic>

class MergeSortMt
{
    public:
        MergeSortMt( std::vector< std::atomic< int > > );
        MergeSortMt( std::vector< std::atomic< int > >, bool );
        void display_elements() const;
    private:
        std::vector< std::atomic< int > > data;
        bool verbose;
        void sort_sub_vector( int, int );
        void merge( int, int, int, int );
        void display_sub_vector( int, int ) const;
};