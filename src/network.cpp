#include "network.h"
#include "random.h"
#include <vector>
#include <stdexcept>
using namespace std;

#include <iostream>

/*!This function resizes (to n) the attribut "values" corresponding to the list of nodes. 
//After that, for each of the element of attribut it generates random value according to normal distribution N(0,1). 
*/ 

void Network::resize(const size_t& n)	                          																							
{
	// l'erreur n<1 est deja geree dans simulation.cpp
  values.clear();
  
  values.resize(n);
  
  RNG.normal(values,0,1);		                       
																																		
}


/*!Addition of a bidirectional link between two different nodes :   <b>(a, b)</b>  and <b>(b, a)</b>
//@param[in] a,b the indexes																		
//@param[out] success the link was succesfully inserted (true if both nodes exist and the link did not exist yet)
*/

bool Network::add_link(const size_t& a, const size_t& b)
{
  if ((a==b) or (a>=size())
			 or (b>=size()) 
			 or (a<0) 
			 or (b<0)){					// check on neighbors conditions
	  return false;
	}
	
  for (auto i : neighbors(a)) {
    if (i==b) return false;				// verification of absence of already existing link between them
  }
    links.insert( { {a,b}, {b,a} } );   // insertion of the new bidirectional link in the container 
    return true;

}

/*! Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes (randomly chosen),
  where *degree(n)* is Poisson-distributed.

  All previous links are erased first.
  @param[in] mean_deg the average of the Poisson distribution,
  @param[out] number of links created.
 */
 

size_t Network::random_connect(const double& mean_deg)
{
	/*! exeption qui est geree dans le main 
	 * portion de code a ajouter dans le main de l'enonce, a la suite du premier *catch* dans la boucle du *try*: 
	 * catch (std::invalid_argument &e) { //catch string errors thrown during the running program. Here they are treated by a display on the terminal
        std::cerr << e.what() << std::endl;
        errcode = 1;
	 */
  if ((mean_deg > size()-1) or (mean_deg<1)) {
  throw invalid_argument (" mean_deg : entrer un chiffre positif qui n'excede pas le nbr de noeuds - 1");}
  
  
  links.clear();
  size_t resultat (0);

  vector<int> poisson_tab ( size() );
  RNG.poisson(poisson_tab, mean_deg); 

  vector <size_t> list_linked_nodes (values.size());
  
  for (size_t j = 0; j<list_linked_nodes.size(); ++j) {
    list_linked_nodes[j]=j;
  }

  for (int n=0; n<values.size() ; ++n) {
    RNG.shuffle(list_linked_nodes);

    size_t h (0);
    
    for (int i=0; i<poisson_tab[n] && h<list_linked_nodes.size(); ++h) {
      if (add_link(n, list_linked_nodes[h])) {
		  resultat++; i++;
		  }
    }
  }
  return resultat;
}



/*! Resets node values with a vector of *n* new values.
  If the current size is *s* and *n<s* then only the first *n* values are changed.
  If *n>s* then only *s* values are used. 
  The internal \ref values vector keeps the same size.

  @param[in] vector of new node values,
  @param[out] number of nodes succesfully reset.
 */
  
size_t Network::set_values(const std::vector<double>& tableau_new_val)
{
  // All previous nods are cleares first
  values.clear();
  
  values.resize(tableau_new_val.size()); 														
  values = tableau_new_val;
  
  return tableau_new_val.size();
}

/*! Number of nodes */

size_t Network::size() const
{
  return values.size(); // number of nods correspond to size of their container
}

/*! Degree (number of links) of node no *n* */

size_t Network::degree(const size_t & _n) const
{
  return links.count(_n);
}

/*! Value of node no *n* */

double Network::value(const size_t & _n) const
{
  if ( _n>=size() or _n<0 ) {
    throw invalid_argument ("Essai d'acces hors du tableau contenant les *values*"); // exeption geree dans le main
  }
  else {
	  return values[_n];
  }
}

/*! All node values in descending order.
    \ref values is left unchanged by this operation.
 */
 
vector<double> Network::sorted_values() const
{
  vector<double> sorted_value (values);
  sort(sorted_value.begin(), sorted_value.end(), greater<double>());   // template function *greater* sort it the decreasing order 
  
  return sorted_value;
}

/*!All neighbors (linked) nodes of node no *n* */

vector<size_t> Network::neighbors(const size_t& n) const
{
  // container of neigbors
  vector<size_t> tab_ngbt (0);
  
  if (n>= 0 and n<size()) { 																					
    auto interval = links.equal_range(n);																		
    for (auto i = interval.first; i != interval.second; ++i) { 			//crosses all occurence on n 		
      tab_ngbt.push_back( i->second ) ; 								// additions of values of nod with which n is linked to container																
    }
  }
  return tab_ngbt;
}
