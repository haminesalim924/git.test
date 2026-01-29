contactdata=[ 

        { "id": 1, "nom": "Dupont", "prenom": "Marie", "email": "marie.dupont@email.com", "telephone": "06 12 34 56 78" }, 

        { "id": 2, "nom": "Martin", "prenom": "Pierre", "email": "pierre.martin@email.com", "telephone": "06 98 76 54 32" }, 

        { "id": 3, "nom": "Bernard", "prenom": "Sophie", "email": "sophie.bernard@email.com", "telephone": "06 11 22 33 44" } 

    ] 
const contactsList= document.getElementById("contacts-list");
const nodeInfo= document.getElementById("node-info");
const btnLoad= document.getElementById("btn-load");
const btnPrev= document.getElementById("btn-prev");
const btnNext= document.getElementById("btn-next");
const btnParent= document.getElementById("btn-parent");
const btnChildren= document.getElementById("btn-children");
     
console.log("Titre de la page :", document.title);
console.log("Body du document :", document.body);
console.log("Élément racine (HTML) :", document.documentElement);

function loadContacts() {
	contactsList.innerHTML = "";
	contactsData.forEach(contact => {
		const card = createContactCard(contact);
		contactsList.appendChild(card);
	});
}
btnLoad.addEventListener("click", loadContacts);
function selectElement(element){
	if(selectedElement){
		selectedElement.classList.remove("selected");
	}
	selectedElement=element;
	selectedElement.classList.add("selected");
	displayNodeInfo();
}
function displayNodeInfo(){
	if(!selectedElement){
		nodeInfo.textContent="Aucun élément sélectionné";
		return;
	}

	nodeInfo.innerHTML=
		"Nom du nœud : "+selectedElement.nodeName+"<br>"+
		"Parent : "+selectedElement.parentNode.nodeName+"<br>"+
		"Nombre total de nœuds enfants : "+selectedElement.childNodes.length+"<br>"+
		"Nombre d'éléments enfants : "+selectedElement.children.length+"<br>"+
		"Premier enfant : "+(selectedElement.firstChild?selectedElement.firstChild.nodeName:"null")+"<br>"+
		"Dernier enfant : "+(selectedElement.lastChild?selectedElement.lastChild.nodeName:"null")+"<br>"+
		"Frère précédent élément : "+(selectedElement.previousElementSibling?selectedElement.previousElementSibling.nodeName:"null")+"<br>"+
		"Frère suivant élément : "+(selectedElement.nextElementSibling?selectedElement.nextElementSibling.nodeName:"null");
}
contactsList.addEventListener("click",event=>{
	const card=event.target.closest(".contact-card");
	if(card){
		selectElement(card);
	}
});
btnParent.addEventListener("click",()=>{
	if(selectedElement){
		const parent=selectedElement.parentNode;
		if(parent && parent!==document.body && parent!==document.documentElement){
			selectElement(parent);
		}
	}
});

btnChildren.addEventListener("click",()=>{
	if(selectedElement && selectedElement.children.length>0){
		selectElement(selectedElement.firstElementChild);
	}
});
