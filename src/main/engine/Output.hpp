/* ---------------------------------------------------------------------
 * Numenta Platform for Intelligent Computing (NuPIC)
 * Copyright (C) 2013, Numenta, Inc.  Unless you have an agreement
 * with Numenta, Inc., for a separate license for this software code, the
 * following terms and conditions apply:
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses.
 *
 * http://numenta.org/licenses/
 * ---------------------------------------------------------------------
 */

/** @file 
 * Interface for the internal Output class.
 */

#ifndef NTA_OUTPUT_HPP
#define NTA_OUTPUT_HPP

#include <set>
#include <nta/types/types.hpp>
#include <nta/utils/Log.hpp> // temporary, while impl is in this file
namespace nta
{

  class Link;
  class Region;
  class Array;

  /**
   * Represents a named output to a Region.
   */
  class Output
  {
  public:

    /**
     * Constructor.
     * 
     * @param region
     *        The region that this Output object belongs to.
     * @param type
     *        The type of the output, TODO
     * @param isRegionLevel
     *        Whether the Output object is region level, i.e. TODO
     */
    Output(Region& region, NTA_BasicType type, bool isRegionLevel);

    /**
     * Destructor
     */
    ~Output();

    /**
     * Set the name for the Output object.
     * 
     * Output need to know their own name for error messages.
     * 
     * @param name
     *        The name of the Output object
     */
    void setName(const std::string& name);

    /**
     * Get the name of the Output object.
     * 
     * @return 
     *        The name of the Output object 
     */
    const std::string& getName() const;
    
    /** 
     * Initialize the Output .
     *
     * @param size
     *        The count of node output element, i.e. TODO
     *
     * @note It's safe to reinitialize an initialized Output with the same 
     * parameters.
     * 
     */
    void initialize(size_t size);

    /**
     *
     * Add a Link to the Output .
     *
     * @note The Output does NOT take ownership of @a link, it's created and 
     * owned by an Input Object.
     *
     * Called by Input.addLink()
     * 
     * @param link
     *        The Link to add
     */
    void
    addLink(Link* link);

    /**
     * Removing an existing link from the Output object.
     * 
     * @note Called only by Input.removeLink() even if triggered by 
     * Network.removeRegion() while removing the region that contains us.
     * 
     * @param link
     *        The Link to remove
     */
    void
    removeLink(Link*);

    /**
     * Tells whether the Output object has outgoing links, i.e. TODO
     * 
     * @note We cannot delete a region if there are any outgoing links
     * This allows us to check in Network.removeRegion() and Network.~Network().
     * @returns
     *         Whether the Output object has outgoing links
     */
    bool
    hasOutgoingLinks();

    /** 
     *
     * Get the data of the Output object.
     *
     * @returns
     *         A constant reference to the data of the output as an @c Array
     *         
     * @note It's mportant to return a const array so caller can't
     * reallocate the buffer.
     */
    const Array &
    getData() const;

    /** 
     * 
     * Tells whether the Output object is region level, i.e. TODO
     * 
     * @returns
     *     Whether the Output object is region level, i.e. TODO
     */
    bool
    isRegionLevel() const;

    /**
     *
     * Get the Region that this Output object belongs to.
     * 
     * @returns
     *         The mutable reference to the Region that this Output object belongs to
     */
    Region&
    getRegion() const;

    /**
     * Get the count of node output element.
     * 
     * @returns
     *         The count of node output element, previously set by initialize().
     */
    size_t
    getNodeOutputElementCount() const;

  private:

    Region& region_; // needed for number of nodes
    Array * data_;
    bool isRegionLevel_;
    // order of links never matters, so store as a set
    // this is different from Input, where they do matter
    std::set<Link*> links_;
    std::string name_;
    size_t nodeOutputElementCount_;
  };

}


#endif // NTA_OUTPUT_HPP
