/**
 * @param {number} numCourses
 * @param {number[][]} prerequisites
 * @return {number[]}
 */
var findOrder = function (numCourses, prerequisites) {
    let sortedOrder = [];
    // if n is smaller than or equal to zero we will
    // return the empty array
    if (numCourses <= 0) {
        return sortedOrder;
    }

    let inDegree = {};
    let graph = {};
    // Store the count of incoming prerequisites in a
    // hashmap
    for (let i = 0; i < numCourses; i++) {
        inDegree[i] = 0;
    }
    // a. Initialize the graph
    for (let i = 0; i < numCourses; i++) {
        graph[i] = []; // adjacency list graph
    }

    // b. Build the graph
    prerequisites.forEach((edge) => {
        let parent = edge[1];
        let child = edge[0];
        graph[parent].push(child); // put the child into it's parent's list
        inDegree[child] += 1; // increment child's inDegree
    });

    // c. Find all sources i.e., all nodes with 0
    // in-degrees
    let sources = new FIFO();
    Object.keys(inDegree).forEach((key) => {
        if (inDegree[key] == 0) {
            sources.enqueue(key);
        }
    });

    // d. For each source, add it to the sortedOrder and
    // subtract one from all of its children's in-degrees.
    // If a child's in-degree becomes zero, add it to the
    // sources queue
    while (sources.length != 0) {
        // pop an element from the start of the sources and
        // store the element in vertex
        let vertex = sources.dequeue();
        // append the vertex at the end of the sortedOrder
        sortedOrder.push(vertex);
        // traverse in graph[vertex] using child get the
        // node's children to decrement their in-degrees
        graph[vertex].forEach((child) => {
            inDegree[child] -= 1;
            if (inDegree[child] == 0) {
                sources.enqueue(child);
            }
        });
    }
    // topological sort is not possible as the graph has a
    // cycle
    if (sortedOrder.length != numCourses) {
        return [];
    }

    return sortedOrder;
};

class FIFO {
    constructor() {
        this.elements = {};
        this.head = 0;
        this.tail = 0;
    }
    enqueue(element) {
        this.elements[this.tail] = element;
        this.tail++;
    }
    dequeue() {
        const item = this.elements[this.head];
        delete this.elements[this.head];
        this.head++;
        return item;
    }
    peek() {
        return this.elements[this.head];
    }
    get length() {
        return this.tail - this.head;
    }
    get isEmpty() {
        return this.length === 0;
    }
}
