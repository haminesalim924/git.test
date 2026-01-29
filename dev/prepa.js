contactsData=[
        { "id": 1, "nom": "Dupont", "prenom": "Marie", "email": "marie.dupont@email.com", "telephone": "06 12 34 56 78" },
        { "id": 2, "nom": "Martin", "prenom": "Pierre", "email": "pierre.martin@email.com", "telephone": "06 98 76 54 32" },
        { "id": 3, "nom": "Bernard", "prenom": "Sophie", "email": "sophie.bernard@email.com", "telephone": "06 11 22 33 44" }
    ]
let contactslist=document.getElementById("contacts-list")
let nodeinfo=document.getElementById("node-info")
let btnload=document.getElementById("btn-load")
let btnprev=document.getElementById("btn-prev")
let btnnext=document.getElementById("btn-next")
let btnparent=document.getElementById("btn-parent")
let btnchildren=document.getElementById("btn-children")
let title=document.title
console.log(title)
let body=document.body
console.log(body)
let root=document.documentElement
console.log(root)
function createcontactcard(contact){
     function createContactCard(contact) {

    let div = document.createElement("div");
    div.className = "contact-card"; // conforme au cours

    let h3 = document.createElement("h3");
    h3.textContent = contact.prenom + " " + contact.nom;

    let pEmail = document.createElement("p");
    pEmail.textContent = contact.email;

    let pTel = document.createElement("p");
    pTel.textContent = contact.telephone;

    div.appendChild(h3);
    div.appendChild(pEmail);
    div.appendChild(pTel);

    return div;
}

}
createcontactcard(contactsData[0])