 var graph = {
	nodes: [
 	 	{ id: "n0", label: "0", x: 0, y: 0, size: 80, color: '#18894836'},
 	 	{ id: "n1", label: "1", x: 0.58, y: 1.1, size: 106, color: '#255'},
 	 	{ id: "n2", label: "2", x: 1.36, y: -0.08, size: 80, color: '#18894836'},
 	 	{ id: "n3", label: "3", x: 0.48, y: 1.13, size: 74, color: '#16378256'}
 	],
	edges: [
 	 	{ id: "e0", source: "n0" , target: "n1", color: '#65280', type:'line', size: 19.5},
 	 	{ id: "e1", source: "n0" , target: "n2", color: '#65280', type:'line', size: 19.5},
 	 	{ id: "e2", source: "n1" , target: "n2", color: '#65280', type:'line', size: 19.5},
 	 	{ id: "e3", source: "n1" , target: "n3", color: '#65280', type:'line', size: 5 },
 	] 
}