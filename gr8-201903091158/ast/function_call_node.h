#ifndef __GR8_AST_FUNCTION_CALL_H__
#define __GR8_AST_FUNCTION_CALL_H__

#include <string>
#include <cdk/ast/basic_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/nil_node.h>
#include <cdk/ast/expression_node.h>
#include "targets/basic_ast_visitor.h"

namespace gr8 {

  /**
   * Class for describing function call nodes.
   *
   * If _arguments is null, them the node is either a call to a function with
   * no arguments (or in which none of the default arguments is present) or
   * an access to a variable.
   */
  class function_call_node: public cdk::expression_node {
    std::string _identifier;
    cdk::sequence_node *_arguments;

  public:
    /**
     * Constructor for a function call without arguments.
     * An empty sequence is automatically inserted to represent
     * the missing arguments.
     */
    function_call_node(int lineno, const std::string &identifier) :
        cdk::expression_node(lineno), _identifier(identifier), _arguments(new cdk::sequence_node(lineno)) {
    }

    /**
     * Constructor for a function call with arguments.
     */
    function_call_node(int lineno, const std::string &identifier, cdk::sequence_node *arguments) :
        cdk::expression_node(lineno), _identifier(identifier), _arguments(arguments) {
    }

  public:
    const std::string &identifier() {
      return _identifier;
    }
    cdk::sequence_node *arguments() {
      return _arguments;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_call_node(this, level);
    }

  };

} // gr8

#endif
