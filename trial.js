 var graph = {
	nodes: [
 	 	{ id: "n0", label: "A", x: 3, y: 1, size: 4, color: '#579720'},
 	 	{ id: "n1", label: "B", x: 4, y: 2, size: 5, color: '#739502'},
 	 	{ id: "n2", label: "C", x: 5, y: 3, size: 2.6, color: '#356024'},
 	 	{ id: "n3", label: "D", x: 0, y: 0, size: 5, color: '#739502'}
 	],
	edges: [
 	 	{ id: "e0", source: "n0" , target: "n2", color: '#16777200', type:'line', size: 5},
 	 	{ id: "e1", source: "n1" , target: "n0", color: '#1677720', type:'line', size: 0.95},
 	 	{ id: "e2", source: "n0" , target: "n3", color: '#8388600', type:'line', size: 2.75},
 	 	{ id: "e3", source: "n3" , target: "n1", color: '#1677720', type:'line', size: 0.95},
 	 	{ id: "e4", source: "n2" , target: "n3", color: '#6710880', type:'line', size: 5 },
 	] 
}