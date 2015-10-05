// ----------------------------------------------------------------------------------------------------------
/// @file   Header file for parahaplo node container class and the structs which it uses
// ----------------------------------------------------------------------------------------------------------

#ifndef PARHAPLO_NODE_CONTAINER_HPP
#define PARHAPLO_NODE_CONTAINER_HPP

#include "devices.hpp"
#include <tbb/tbb.h>

namespace haplo {

// ----------------------------------------------------------------------------------------------------------
/// @class     Node
/// @brief      Each node has a weight and and index, the index represents the position which the node models
///             in the haplotype and the weight is the significance of the variable
// ----------------------------------------------------------------------------------------------------------
class Node {
private:
    size_t _weight;     //!< The weight of the node (how important it is)
    size_t _haplo_pos;      //!< The position in the haplotype the node represents
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor for initialization
    // ------------------------------------------------------------------------------------------------------
    Node() noexcept : _weight(1), _haplo_pos(0) {}

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Destructor for node class
    // ------------------------------------------------------------------------------------------------------
    ~Node() noexcept {}
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Accessor for the weight
    /// @return     A reference to the weight
    // ------------------------------------------------------------------------------------------------------
    inline size_t& weight() { return _weight; }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Accessor for the weight
    /// @return     A constant reference to the weight
    // ------------------------------------------------------------------------------------------------------
    inline const size_t& weight() const { return _weight; }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Accessor for the haplo position
    /// @return     A reference to haplo position
    // ------------------------------------------------------------------------------------------------------
    inline size_t& position() { return _haplo_pos; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns the value of the node so that it cant be used by sorting function
    /// @return     The value (weight of the node)
    // ------------------------------------------------------------------------------------------------------
    inline size_t value() const { return _weight; }
};

// ----------------------------------------------------------------------------------------------------------
/// @class     Link
/// @brief      A link between two nodes, there is a homozygous component -- how strongly correlated the nodes
///             are (that they should have the same value) -- and a heterozygous component -- how stongly they
///             should be different.
// ----------------------------------------------------------------------------------------------------------
class Link {
private:  
    tbb::atomic<size_t> _homo_weight;        //!< Weight of the link if the nodes have the same ideal values
    tbb::atomic<size_t> _hetro_weight;       //!< Weight of the link if the nodes have different ideal values
public:
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Default constructor for initialization
    // ------------------------------------------------------------------------------------------------------
    Link() noexcept : _homo_weight(0), _hetro_weight(0) {}
   
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Destructor for link class
    // ------------------------------------------------------------------------------------------------------
    ~Link() noexcept {}
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Accessor for the homozygous weight 
    /// @return     A reference to the homozygous weight
    // ------------------------------------------------------------------------------------------------------
    inline tbb::atomic<size_t>& homo_weight() { return _homo_weight; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Accessor for the heteroygous weight 
    /// @return     A reference to the heteroygous weight
    // ------------------------------------------------------------------------------------------------------
    inline tbb::atomic<size_t>& hetro_weight() { return _hetro_weight; }

    // ------------------------------------------------------------------------------------------------------
    /// @brief      Const ccessor for the homozygous weight 
    /// @return     A cosnt reference to the homozygous weight
    // ------------------------------------------------------------------------------------------------------
    inline const tbb::atomic<size_t>& homo_weight() const { return _homo_weight; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Const ccessor for the heteroygous weight 
    /// @return     A const reference to the heteroygous weight
    // ------------------------------------------------------------------------------------------------------
    inline const tbb::atomic<size_t>& hetro_weight() const { return _hetro_weight; }
    
    // ------------------------------------------------------------------------------------------------------
    /// @brief      Returns the value of the link so that it cant be used bya sorting function
    /// @return     The value (maximum weight of the node)
    // ------------------------------------------------------------------------------------------------------
    inline size_t value() const { return std::max(_homo_weight, _hetro_weight); }
};

// ----------------------------------------------------------------------------------------------------------
/// @class      NodeContainer 
/// @brief      Holds nodes for the tree that needs to be searched. The container is structured as follows:
///             The information for each of the nodes is stored first
///
///             [{weight0,index0}, {weight1,index1}, ..., {weightN,indexN}]
///
///             Then the link weights for the connections between the nodes is stored:
///
///             [{how01,hew01}, {how02,hew02},...,{how0N,hew0N},{how12,hew12},....{how(N-1)N,hew(N-1)N}]
///
///             where:
///
///             howAB = homozygous weight between node A and B
///             hewAB = heterozygous weight between node A and B
/// @tparam     DeviceType      The type of device being used
// ----------------------------------------------------------------------------------------------------------
template <uint8_t DeviceType>
class NodeContainer;

}           // End namespace haplo
#endif      // PARAHAPLO_NODE_CONTAINER_HPP

