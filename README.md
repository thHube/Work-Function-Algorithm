<h2>Work Function Algorithm</h2>
This is a C++ implementation of the work function algorithm for Approximation 
Algorithm class held by Livio Colussi at Univerit&agrave; degli Studi di Padova.

<h3>Optimization - [Up to date, more to come]</h3>
Respect to classical algorithm we have done some optimizations. 
<ul>
    <li>
        Object paged onto memory with a given page size (we use 256 as page 
        size). This help reducing memory allocation/dellocation. 
    </li>
    <li>
        Recursion depth is clamped to k + 1, you can prove that this is enough
        to keep the algorithm (2k + 1)-competitive but infinitely more 
        efficient.
    </li>
</ul>

