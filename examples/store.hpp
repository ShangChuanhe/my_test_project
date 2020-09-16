/*
	    Welcome to my world!!
	         Just do it
                       ------------The final right of interpretation belongs to Mr. Shang
*/

#include <mockturtle/mockturtle.hpp>
#include <mockturtle/io/write_verilog.hpp>
#include <alice/alice.hpp>
#include <fmt/format.h>
#include <kitty/kitty.hpp>
/*
#include "networks/m5ig/m5ig.hpp"
#include "networks/img/img.hpp"
#include "networks/img/img_verilog_reader.hpp"
*/
using namespace mockturtle;

namespace alice
{
    /*****************************************************
    ******************General store***********************
     ****************************************************/

    /***************************************************** 
     * Add Aiger Store Type                             *
     ****************************************************/
    /*
     * One can access AIGs in general store commands using the long --aig flag or 
     * the short -a flag.
     */
    ALICE_ADD_STORE(mockturtle::aig_network, "aig", "a", "AIG", "AIGs")

    /* Implements the functionality of ps -a */
    ALICE_PRINT_STORE(mockturtle::aig_network, os, element )
    {
	os << "AIG PI/PO = " << element.num_pis() << "/" << element.num_pos() << "\n";
    }

    /* Implements the short string to describe a store element in store -a */
    ALICE_DESCRIBE_STORE(mockturtle::aig_network, element )
    {
	return fmt::format( "{} nodes", element.size() );
    }
    

    /*****************************************************
    ******************Read and Write**********************
     ****************************************************/


    /* Use ALICE_ADD_FILE_TYPE() will create two commands read_aiger and  write_aiger.*/
    

    /**************************************************** 
     * Add an Aiger file type                           *
    ****************************************************/
    ALICE_ADD_FILE_TYPE(aiger, "Aiger");
    
    /* Implements the functionality of read_aiger -a */
    ALICE_READ_FILE(mockturtle::aig_network, aiger, filename, cmd)
    {
	mockturtle::aig_network aig;
	lorina::read_aiger(filename, mockturtle::aiger_reader(aig));
	return aig;
    }

    /* Implements the functionality of ps -a */
    ALICE_PRINT_STORE_STATISTICS(mockturtle::aig_network, os, aig)
    {
	mockturtle::depth_view depth_aig{aig};
	os << fmt::format("AIG  i/o = {}/{}  gate = {}  level = {}",
	      aig.num_pis(), aig.num_pos(), aig.num_gates(), depth_aig.depth());
	os << "\n";
    }


    /**************************************************** 
     * Add an Verilog file type                           *
    ****************************************************/
    ALICE_ADD_FILE_TYPE(verilog, "Verilog");

    ALICE_READ_FILE(mockturtle::aig_network, verilog, filename, cmd)
    {
	mockturtle::aig_network aig;
	
	lorina::diagnostic_engine diag;
	if( lorina::read_verilog(filename, mockturtle::verilog_reader(aig), &diag) != lorina::return_code::success)
	{
	    std::cout << "[w] parse error";
	}
	return aig;
    }

/*    ALICE_PRINT_STORE_STATISTICS(aig_network, os, aig)
    {
	mockturtle::depth_view depth_aig{aig};
	os << fmt::format("AIG  i/o = {}/{}  gate = {}  level = {}",
	      aig.num_pis(), aig.num_pos(), aig.num_gates(), depth_aig.depth());
	os << "/n";	
    }
*/
    /**************************************************** 
     * Add an Bench file type                           *
    ****************************************************/
/*    ALICE_ADD_FILE_TYPE(bench, "BENCH");
    
    AILCE_READ_FILE(mockturtle::klut_network, bench, filename, cmd)
    {
	mockturtle::klut_network klut;
	lorina::read_bench(filename, mockturtle::bench_reader(klut));
	return klut;
    }
*/
    /* Implements the functionality of write_aiger -a */
    ALICE_WRITE_FILE(mockturtle::aig_network, aiger, aig, filename, cmd)
    {
	mockturtle::write_bench(aig, filename);
    }
    
    /* Implements the functionality of write_verilog -a */
    ALICE_WRITE_FILE(mockturtle::aig_network, verilog, aig, filename, cmd)
    {
	mockturtle::write_verilog(aig, filename);
    }
}
