//
// Copyright (C) 2014 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_APSKSYMBOL_H
#define __INET_APSKSYMBOL_H

//#include "common/Complex.h"
#include <complex>
#include "physicallayer/contract/bitlevel/ISymbol.h"

namespace inet {

namespace physicallayer {

class INET_API APSKSymbol : public std::complex<double>, public ISymbol
{
  public:
    APSKSymbol() : std::complex<double>() {}
    APSKSymbol(const double& r) : std::complex<double>(r) {}
    APSKSymbol(const double& q, const double& i) : std::complex<double>(q, i) {}
    APSKSymbol(const std::complex<double>& w) : std::complex<double>(w) {}
};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_APSKSYMBOL_H

