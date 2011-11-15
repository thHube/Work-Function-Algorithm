<h2>Work Function Algorithm</h2>
This is a C++ implementation of the work function algorithm for Approximation 
Algorithm class held by Livio Colussi at Universit&agrave; degli Studi di Padova

<h3>Optimization - [Up to date, more to come]</h3>
Respect to classical algorithm we have done some optimizations. 
<ul>
    <li>
        Object are paged onto memory with a given page size (we use 256 as page 
        size). This help reducing memory allocation/dellocation. 
    </li>
    <li>
        To perform less calculations we control that the diequation 
        <code>upperBound - partialSum >= distanceFromOrigin(newConfiguration)</code>
        must be always satisfied. 
    </li>
</ul>

