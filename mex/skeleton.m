function [ext, bas, edges, totalnumrays, totalnumedges] = ...
        skeleton(ine, equ, options, zerotol)
    
% Skeleton finds the explicit representation of a polyhedral cone.
%
% [ext, bas, edges, totalnumrays, totalnumedges] = ...
%    skeleton(ine, equ, options, zerotol)
%
% Skeleton uses the program Skeleton, www.uic.nnov.ru/~zny/skeleton
%
% The cone is defind as the set of all solution to the system
% ine*x >= 0, equ*x == 0. The function returns irreducible systems
% ext and bas such that the cone is the set of all non-negative
% combinations of the rows in ext plus the set of all combinations of the
% rows in bas.
%
% options is a string containing parameters separated by the space char.
% The following options are available: minindex, maxindex, lexmin, lexmax,
% mincutoff, maxcutoff, random, minpairs, maxpairs, prefixedorder,
% noprefixedorder, graphadj, nographadj, plusplus, noplusplus. Their
% description see in Skeleton manual.
%
% zerotol is the zero tolerance; 1e-6, by default.
%
% edges is the list of all pairs of incident vectors in ext.
%
% totalnumrays and totalnumedges are the total number of all rays and edges
% correspondingly constructed during the algorithm.

% Nikolai Yu. Zolotykh, 2009

% This program is free software; you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation; either version 2 of the License, or
% (at your option) any later version.
%
% This program is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
%
% You should have received a copy of the GNU General Public License
% along with this program; if not, write to the Free Software
% Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    if nargin < 1
        skeletonmx;
        return
    end
    if nargin < 2
        equ = [];
    end
    if nargin < 3 || isempty(options)
        options = '';
    end
    if nargin < 4 || isempty(zerotol)
        zerotol = 1e-6;
    end
    
    if nargout < 3
        edgesflag = 0;
    else
        edgesflag = 1;
    end
    
    order = 0;
    prefixedorder = 1;
    graphadj = 1;
    plusplus = 1;
    
    for optcell = regexp(options, '\s+', 'split')
        opt = optcell{1};
        switch opt
            case ''
            case 'minindex'
                order = 0;
            case 'maxindex'
                order = 1;
            case 'lexmin'
                order = 2;
            case 'lexmax'
                order = 3;
            case 'mincutoff'
                order = 4;
            case 'maxcutoff'
                order = 5;
            case 'random'
                order = 6;
            case 'minpairs'
                order = 7;
            case 'maxpairs'
                order = 8;
            case 'prefixedorder'
                prefixedorder = 1;
            case 'noprefixedorder'
                prefixedorder = 0;
            case 'graphadj'
                graphadj = 1;
            case 'nographadj'
                graphadj = 0;
            case 'plusplus'
                plusplus = 1;
            case 'noplusplus'
                plusplus = 0;
            otherwise
                warning('Skeleton:unknownOption', ['Unknown option :', opt])
        end
    end
    
    [ext, bas, dis, edges, totalnumrays, totalnumedges] = ...
        skeletonmx(ine, equ, edgesflag, ...
        order, prefixedorder, graphadj, plusplus, zerotol);
    
    if nargout < 2 && ~isempty(bas)
        warning('Skeleton:basisIsNotEmpty', 'Basis found is not empty.')
    end