#ifndef JPLOT_H
#define JPLOT_H

//C System-Headers
#include <cstdarg>
//C++ System headers
#include <utility>
//OpenCL Headers

//Boost Headers

//GnuPlot Headers
#include "gnuplot-iostream.h"
//Project specific headers
#include "../JASPL/jTypeTraits/jtypetraits.h"

namespace jaspl {

template < typename T >
class Plotter {

    typedef std::pair< T, std::string > series_pair;

  public:
    Plotter() {
        static_assert(is_stdlib_container< T >::value,
                      "Can only plot container-like objects.");
        static_assert(std::is_arithmetic< typename T::value_type >::value,
                      "Can only plot arithmetic types.");
    }

    ~Plotter();

    void Plot() {
        //
    }

    void SetXAxisLabel( std::string x_label ) {
        //
    }

    void SetYAxisLabel( std::string y_label ) {

    }

    void SetSavePath( std::string file_path ) {

    }

    void AddSeries( T series, std::string title ) {
        series_list.push_back( series_pair( series, title ) );
    }

    void SetMaxNumPoints( uint max_points ) {
        //
    }

  private:

    T decimate( const T& series, uint desired_points ) {
        uint pivot = static_cast<uint> (series.size() / desired_points);

        std::vector<uint> pivot_indices;

        for( uint i = 0 ; i < series.size() ; i ++ ) {
            if ( i%pivot == 0 ) {
                pivot_indices.push_back(i);
            }
        }

        T y_vals;

        for ( const auto& idx : pivot_indices ) {
            y_vals.push_back( series.at(idx) );
        }
    }

    std::string save_file_path;
    std::string x_label;
    std::string y_label;
    uint max_num_points;

    std::list< series_pair > series_list;
    Gnuplot gp;
};

template <typename T> void plot( T signal ) {

    static_assert(is_stdlib_container< T >::value,
                  "Can only plot container-like objects.");
    static_assert(std::is_arithmetic< typename T::value_type >::value,
                  "Can only plot arithmetic types.");

    Gnuplot gp;

    gp << "plot '-' with lines notitle\n";
    gp.send1d(signal);
}

template <class T> void plot ( T signal, uint num_plot_points ) {

    static_assert(is_stdlib_container< T >::value,
                  "Can only plot container-like objects.");
    static_assert(std::is_arithmetic< typename T::value_type >::value,
                  "Can only plot arithmetic types.");

    Gnuplot gp;

    uint pivot = static_cast<uint> (signal.size() / num_plot_points);

    std::vector<uint> pivot_indices;

    for( uint i = 0 ; i < signal.size() ; i ++ ) {
        if ( i%pivot == 0 ) {
            pivot_indices.push_back(i);
        }
    }

    T y_vals;

    for ( const auto& idx : pivot_indices ) {
        y_vals.push_back( signal.at(idx) );
    }

    gp << "plot '-' with lines notitle\n";
    gp.send1d(y_vals);
}


//friend function of JVector
template <class T> void plot ( T& signal, std::string plot_title ) {

    static_assert(is_stdlib_container< T >::value,
                  "Can only plot container-like objects.");
    static_assert(std::is_arithmetic< typename T::value_type >::value,
                  "Can only plot arithmetic types.");

    Gnuplot gp;

    gp << "set title '"+plot_title+"'\n";
    gp << "plot '-' with lines notitle\n";
    gp.send1d(signal);
}

template <class T>
void plot_to_disk ( T& signal_a,
                    std::string signal_a_title,
                    std::string x_axis_label,
                    std::string y_axis_label,
                    std::string plot_title,
                    std::string save_file_path ) {

    static_assert(is_stdlib_container< T >::value,
                  "Can only plot container-like objects.");
    static_assert(std::is_arithmetic< typename T::value_type >::value,
                  "Can only plot arithmetic types.");

    Gnuplot gp;

    std::string out_file_path = save_file_path + plot_title + ".png";

    gp <<  "set term png transparent truecolor size 1280,720\n";
    gp << " set border lw 3 lc rgb 'yellow' " << std::endl;
    gp << " set key font ', 20' textcolor rgb 'yellow' " << std::endl;
    gp << "set output '"+out_file_path+"'\n";
    gp << "set xlabel font ', 20' " << std::endl;
    gp << "set ylabel font ', 20' " << std::endl;
    gp << "set xlabel '" + x_axis_label + "' tc rgb 'yellow' " << std::endl;
    gp << "set ylabel '" + y_axis_label + "' tc rgb 'yellow' " << std::endl;
    gp << "set xtics font ', 20' tc rgb 'yellow'" << std::endl;
    gp << "set ytics font ', 20' tc rgb 'yellow'" << std::endl;
    gp << "set title '"+plot_title+"'  font 'arial,30' tc rgb 'yellow' \n";
    gp << "plot" << gp.file1d( signal_a ) << "with lines linewidth 5 title '" + signal_a_title + "'" << std::endl;

}

template <class T>
void plot_to_disk ( T& signal_a,
                    T& signal_b,
                    std::string signal_a_title,
                    std::string signal_b_title,
                    std::string x_axis_label,
                    std::string y_axis_label,
                    std::string plot_title,
                    std::string save_file_path ) {

    static_assert(is_stdlib_container< T >::value,
                  "Can only plot container-like objects.");
    static_assert(std::is_arithmetic< typename T::value_type >::value,
                  "Can only plot arithmetic types.");

    Gnuplot gp;

    std::string out_file_path = save_file_path + plot_title + ".png";

    gp <<  "set term png transparent truecolor size 1280,720\n";
    gp << " set border lw 3 lc rgb 'yellow' " << std::endl;
    gp << " set key font ', 20' textcolor rgb 'yellow' " << std::endl;
    gp << "set output '"+out_file_path+"'\n";
    gp << "set xlabel font ', 20' " << std::endl;
    gp << "set ylabel font ', 20' " << std::endl;
    gp << "set xlabel '" + x_axis_label + "' tc rgb 'yellow' " << std::endl;
    gp << "set ylabel '" + y_axis_label + "' tc rgb 'yellow' " << std::endl;
    gp << "set xtics font ', 20' tc rgb 'yellow'" << std::endl;
    gp << "set ytics font ', 20' tc rgb 'yellow'" << std::endl;
    gp << "set title '"+plot_title+"'  font 'arial,30' tc rgb 'yellow' \n";
    gp << "plot" << gp.file1d( signal_a ) << "with lines linewidth 5 title '" + signal_a_title + "',";
    gp << gp.file1d( signal_b ) << "with lines linewidth 5 title '" + signal_b_title +"'" << std::endl;

}


template <class T> void plot ( T& signal, std::string plot_title, uint num_plot_points ) {

    static_assert(is_stdlib_container< T >::value,
                  "Can only plot container-like objects.");
    static_assert(std::is_arithmetic< typename T::value_type >::value,
                  "Can only plot arithmetic types.");

    Gnuplot gp;

    uint pivot = static_cast<uint> (signal.size() / num_plot_points);

    std::vector<uint> pivot_indices;

    for( uint i = 0 ; i < signal.size() ; i ++ ) {
        if ( i%pivot == 0 ) {
            pivot_indices.push_back(i);
        }
    }

    T y_vals;

    for ( const auto& idx : pivot_indices ) {
        y_vals.push_back( signal.at(idx) );
    }

    gp << "set title '"+plot_title+"'\n";
    gp << "plot '-' with lines notitle\n";
    gp.send1d(y_vals);
}

}

#endif // JPLOT_H
