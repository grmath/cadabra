/* 

   $Id: field_theory.hh,v 1.49 2008/06/28 09:44:33 peekas Exp $

	Cadabra: an extendable open-source symbolic tensor algebra system.
	Copyright (C) 2001-2006  Kasper Peeters <kasper.peeters@aei.mpg.de>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, version 2.
	 
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
	
*/

#ifndef field_theory_hh_
#define field_theory_hh_

#include <string>
#include "manipulator.hh"
#include "props.hh"

/// Classical field theory
namespace field_theory {
	void register_properties();
};

class DependsBase : virtual public property {
	public:
		virtual exptree dependencies(exptree::iterator) const=0;
};

class DependsInherit : public DependsBase, virtual public property {
	public:
		virtual std::string name() const;
		virtual exptree dependencies(exptree::iterator) const;
};

class Depends : public DependsBase, virtual public property {
	public:
		virtual std::string name() const;
		virtual bool parse(exptree&, exptree::iterator, exptree::iterator, keyval_t&);
		virtual exptree dependencies(exptree::iterator) const;
		virtual std::string unnamed_argument() const { return "dependants"; };
	private:
		exptree dependencies_;
};

// class WeightBase : virtual public property {
// 	public:
// 		// A negative number indicates a non-defined weight (e.g "X + \psi \psi")
// 		virtual int  value(exptree::iterator) const=0;
// };
// 
// class Weight : virtual public WeightBase, virtual public property {
// 	public: 
// 		virtual int  value(exptree::iterator) const;
// 		virtual bool parse(exptree&, exptree::iterator, exptree::iterator, keyval_t&);
// 		virtual std::string unnamed_argument() const { return "weight"; };
// 	private:
// 		int value_;
// };
// 
// class WeightInherit : virtual public WeightBase, virtual public property {
// 	public:
// 		virtual bool parse(exptree&, exptree::iterator, exptree::iterator, keyval_t&);
// 		virtual int  value(exptree::iterator) const;
// 		virtual std::string unnamed_argument() const { return "type"; };
// 		
// 		enum { multiplicative, additive } combination_type;
// };
// 
// class GrassmannNumberBase : virtual public WeightBase {
// 	public:
// };
// 
// class GrassmannNumber : public GrassmannNumberBase, public Weight {
// 	public:
// 		virtual std::string name() const;
// };
// 
// class GrassmannNumberInherit : public GrassmannNumberBase, public WeightInherit {
// 	public:
// 		virtual std::string name() const;
// };

class WeightBase : virtual public labelled_property {
	public:
		virtual int  value(exptree::iterator, const std::string& forcedlabel) const=0;
};

class Weight : virtual public WeightBase {
	public: 
		virtual int  value(exptree::iterator, const std::string& forcedlabel) const;
		virtual bool parse(exptree&, exptree::iterator, exptree::iterator, keyval_t&);
		virtual std::string unnamed_argument() const { return "value"; };
		virtual std::string name() const;
	private:
		int value_;
};

class WeightInherit : virtual public WeightBase {
	public:
		virtual bool parse(exptree&, exptree::iterator, exptree::iterator, keyval_t&);
		virtual int  value(exptree::iterator, const std::string& forcedlabel) const;
		virtual std::string unnamed_argument() const { return "type"; };
		virtual std::string name() const;
		
		enum { multiplicative, additive } combination_type;
};

class Accent : public PropertyInherit, public IndexInherit, virtual public property {
	public:
		virtual std::string name() const;
};

class generate_indexbracket : public algorithm {
	public:
		generate_indexbracket(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class unique_indices : public algorithm {
	public:
		unique_indices(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class einsteinify : public algorithm {
	public:
		einsteinify(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class combine : public algorithm {
	public:
		combine(exptree&, iterator);
		
		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
	private:
		typedef std::map<nset_t::iterator, iterator> indexlocmap_t;

		indexlocmap_t iloc;
};

class expand : public algorithm {
	public:
		expand(exptree&, iterator);
		
		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);

		iterator mx_first, mx_last, ii_first, ii_last;
		bool     one_index;
};

class debracket : public algorithm {
	public:
		debracket(exptree&, iterator);
		
		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class eliminate_kronecker : public algorithm {
	public:
		eliminate_kronecker(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class reduce_gendelta : public algorithm {
	public:
		reduce_gendelta(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
	private:
		bool one_step_(sibling_iterator);
};

class break_gendelta : public algorithm {
	public:
		break_gendelta(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class dualise_tensor : public algorithm {
	public:
		dualise_tensor(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class epsprod2gendelta : public algorithm {
	public:
		epsprod2gendelta(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
	private:
		std::vector<iterator> epsilons;
		int                   signature;
		exptree               repdelta;
};

class eliminate_eps : public algorithm {
	public:
		eliminate_eps(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
	private:
		std::vector<iterator> tensors;
		std::vector<iterator> epsilons;
};

class product_shorthand : public algorithm {
	public:
		product_shorthand(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class expand_product_shorthand : public algorithm {
	public:
		expand_product_shorthand(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class remove_eoms : public algorithm {
	public:
		remove_eoms(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class pintegrate : public algorithm {
	public:
	   pintegrate(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);
};

class remove_vanishing_derivatives : public algorithm {
	public:
		remove_vanishing_derivatives(exptree&, iterator);
		
		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);   
};

class unwrap : public algorithm {
	public:
		unwrap(exptree&, iterator);
		
		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);   
};

class impose_bianchi : public algorithm {
	public:
		impose_bianchi(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);

	protected:
		const TableauBase *tb;
};

class all_contractions : public algorithm {
	public:
		all_contractions(exptree&, iterator);

		virtual void     description() const;
		virtual bool     can_apply(iterator);
		virtual result_t apply(iterator&);

	private:
		void create_spinor_contractions(iterator it); // temporary solution

		class iterator_indexgroup_t {
			public:
				iterator_indexgroup_t(const iterator&, int);
				iterator it;
				int      indexgroup;
		};
		class iterator_indexgroup_less {
			public:
				bool operator()(const iterator_indexgroup_t& one, const iterator_indexgroup_t& two) const {
				if(one.it.node < two.it.node) return true;
				if(one.it.node == two.it.node) 
					if(one.indexgroup < two.indexgroup)
						return true;
				return false;
				}
		};
		typedef std::map<iterator_indexgroup_t, std::vector<exptree>, 
							  iterator_indexgroup_less> parent_map_t;

		index_map_t  ind_free, ind_dummy;
		unsigned int number_to_find; 
};

#endif
